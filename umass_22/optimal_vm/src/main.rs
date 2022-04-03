use byteorder::{LittleEndian, ReadBytesExt};

/*
This is the function the bytecode implements to slowly print out the flag. This function is called 
for every bit of the flag with increasingly large numbers. Even input = bit set, uneven input = bit 
not set. 

fn is_even(x: usize) -> usize {
    let mut check = true;
    let mut i = 0;

    loop {
        if i == x {
            if check == true {
                return 1;
            } else if check == false {
                return 0;
            }
        } else {
            i += 1;
            check = !check;
        }
    }
}
*/

#[derive(Debug)]
enum Op {
    Add,
    Be,
    Ll,
    LoadArr,
    Jmp,
    Toggle,
    IsTrue,
    SetupArr,
    StoreArr,
    Finalize,
    Nop,
}

fn convert_op(opcode: u8) -> Op {
    match opcode {
        0x41 => Op::Add,
        0x42 => Op::Be,
        0x43 => Op::Ll,
        0x44 => Op::LoadArr,
        0x45 => Op::Jmp,
        0x46 => Op::Toggle,
        0x47 => Op::IsTrue,
        0x48 => Op::SetupArr,
        0x49 => Op::StoreArr,
        0x50 => Op::Finalize,
        0x51 => Op::Nop,
        _ => panic!("Can't decode: {:x?}", opcode),
    }
}

fn main() {
    let code = std::fs::read("./bin").ok().unwrap();
    let mut pc = 0;
    let mut regs: Vec<u64> = vec![0; 32];
    let mut c: Vec<u8> = vec![0; 8];
    let mut starter: Vec<u64> = vec![0; 8]; 

    while pc < code.len() {
        let opcode = convert_op(code[pc]);
        match opcode {
            Op::Add => {
                let r1 = code[pc+1] as usize;
                let r2 = code[pc+2] as usize;

                let res = regs[r1] + regs[r2];
                regs[r1] = res;

                pc += 3;
            },
            Op::Be => {
                let r1 = code[pc+1] as usize;
                let r2 = code[pc+2] as usize;
                let mut tmp = &code[pc+3..pc+5];
                let r3 = tmp.read_u16::<LittleEndian>().unwrap();

                if regs[r1] == regs[r2] {
                    pc = r3 as usize;
                } else {
                    pc += 5
                }
            },
            Op::Ll => {
                let r1 = code[pc+1] as usize;
                let mut tmp = &code[pc+2..pc+10];
                let imm = tmp.read_u64::<LittleEndian>().unwrap();

                regs[r1] = imm;
                pc += 10
            },
            Op::LoadArr => {
                let r1 = code[pc+1] as usize;
                let r2 = code[pc+2] as usize;

                regs[r1] = starter[regs[r2] as usize] as u64;
                pc += 3;
            },
            Op::StoreArr => {
                let r1 = code[pc+1] as usize;
                let r2 = code[pc+2] as usize;

                c[regs[r1] as usize] = regs[r2] as u8;
                pc += 3;
            },
            Op::Toggle => {
                let r1 = code[pc+1] as usize;
                regs[r1] = (regs[r1] + 1) % 2;
                pc += 2;
            },
            Op::Jmp => {
                let mut tmp = &code[pc+1..pc+3];
                let r1 = tmp.read_u16::<LittleEndian>().unwrap();
                pc = r1 as usize;
            },
            Op::IsTrue => {
                let r1 = code[pc+1] as usize;
                let r2 = code[pc+2] as usize;

                if regs[r1] == 1 {
                    regs[r2] = 1;
                } else {
                    regs[r2] = 0;
                }
                pc += 3;
            },
            Op::SetupArr => {
                let mut offset = 0;
                for i in 0..8 {
                    let mut tmp = &code[pc+1+offset..pc+1+offset+8];
                    starter[i] = tmp.read_u64::<LittleEndian>().unwrap();
                    offset+=8;
                }
                pc += 65;
            },
            Op::Finalize => {
                let mut sum = 0;
                for i in 0..8 {
                    sum += c[i] << (7 - i);
                }
                println!("{}", sum as char);
                pc += 1;
            }
            Op::Nop => {
                pc += 1;
            }
        }
    }
    println!("")
}
