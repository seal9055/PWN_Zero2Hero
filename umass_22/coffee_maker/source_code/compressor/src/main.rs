use rustc_hash::FxHashMap;
use std::{mem, slice};

fn compress(data: &[u8]) -> Vec<u32> {
    // Initialize a codebook that maps a byte sequence to a short index that can be used to to 
    // replace the bytesequence and thus compress the code. This is initialized with single 
    // character strings at the beginning.
    let mut code_book: FxHashMap<Vec<u8>, u32> = FxHashMap::default();
    for i in 0..=255 {
        code_book.insert(vec![i], i as u32);
    }

    let mut tracker = vec![data[0]];
    let mut compressed = Vec::new();

    for &b in &data[1..] {
        let mut cur = tracker.clone();
        cur.push(b);

        // Check if the code book contains tracker + the current byte, if so, extend extend the 
        // tracker with the current byte and keep increasing the combination
        if code_book.contains_key(&cur) {
            tracker.push(b);
        } else {
            // In this case we found a new entry that we can now add to the compressed data
            compressed.push(code_book[&tracker]);

            // Since this is a new entry, we insert this entry into the code book before resetting
            // the tracker
            code_book.insert(cur, code_book.len() as u32);
            tracker.clear();
            tracker.push(b);
        }
    }

    // If the final entry in the file was in the dictionary, we still need to push it to the 
    // compressed data at this point
    if !tracker.is_empty() {
        compressed.push(code_book[&tracker]);
    }

    compressed
}

fn main() {
    // Read chall, compress it and write it to chall_compressed
    let target = std::fs::read("./chal").unwrap();

    let compressed = compress(&target);
    let compressed_u8: &[u8] = unsafe {
        slice::from_raw_parts(
            compressed.as_ptr() as *const u8,
            compressed.len() * mem::size_of::<u32>(),
        )
    };
    std::fs::write("./chal_compressed", compressed_u8).unwrap();
}
