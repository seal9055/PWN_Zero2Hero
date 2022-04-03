use rustc_hash::FxHashMap;
use std::{mem, slice};

fn decompress(data: &[u32]) -> Option<Vec<u8>> {
    // Initialize a codebook that maps an index to its corresponding byte sequence. This is used to
    // gradually build up a decoder while parsing the message and obtaining additional information. 
    // It is initialized with single character strings at the beginning.
    let mut code_book: FxHashMap<u32, Vec<u8>> = FxHashMap::default();
    for i in 0..=255 {
        code_book.insert(i, vec![i as u8]);
    }

    let mut tracker = code_book.get_mut(&data[0])?.to_vec();
    let mut decompressed = tracker.clone();

    for &b in &data[1..] {
        let entry = if code_book.contains_key(&b) {
            code_book[&b].clone()
        } else if b == code_book.len() as u32 {
            let mut e = tracker.clone();
            e.push(tracker[0]);
            e
        } else {
            return None;
        };

        decompressed.extend_from_slice(&entry);

        tracker.push(entry[0]);
        code_book.insert(code_book.len() as u32, tracker);

        tracker = entry;
    }
    Some(decompressed)
}

fn main() {
    // Read chall, compress it and write it to chall_compressed
    let target = std::fs::read("./chal_compressed").unwrap();
    let compressed_u32: &[u32] = unsafe {
        slice::from_raw_parts(
            target.as_ptr() as *const u32,
            target.len() / mem::size_of::<u32>(),
        )
    };

    let decompressed = match decompress(&compressed_u32) {
        Some(data) => data,
        None => panic!("Error occured while decompressing"),
    };
    std::fs::write("./chal", decompressed).unwrap();
}
