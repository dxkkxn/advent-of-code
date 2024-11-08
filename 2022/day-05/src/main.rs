use std::fs::File;
use std::io::Read;

fn main() -> Result<(), std::io::Error> {
    let mut file = File::open("input.txt")?;
    let mut content = String::new();
    file.read_to_string(&mut content)?;
    let (stack, moves) = content.split_once("\n\n").unwrap();
    let v: Vec<&str> = stack.split('\n').collect();
    let n = v
        .last()
        .unwrap()
        .strip_prefix(' ')
        .unwrap()
        .split("  ")
        .count();
    let mut stacks: Vec<Vec<&str>> = Vec::with_capacity(n);
    (0..n).for_each(|_| {
        stacks.push(Vec::new());
    });
    v.iter().rev().skip(1).for_each(|e| {
        let mut first: &str;
        let mut second: &str = e;
        let mut i: usize = 0;
        loop {
            (first, second) = second.strip_prefix(' ').unwrap_or(second).split_at(3);
            if let Some(e) = first.strip_prefix('[') {
                stacks[i].push(e.strip_suffix(']').unwrap());
            }
            i += 1;
            if second.is_empty() {
                break;
            }
        }
    });
    moves
        .lines()
        .map(|l| {
            let (amount, mv) = l
                .strip_prefix("move ")
                .unwrap()
                .split_once(" from ")
                .unwrap();
            let (org, dest) = mv.split_once(" to ").unwrap();
            (
                amount.parse::<usize>().unwrap(),
                org.parse::<usize>().unwrap() - 1,
                dest.parse::<usize>().unwrap() - 1,
            )
        })
        // part 1
        // .for_each(|(amount, org, dest)| {
        //     for _ in 0..amount {
        //         let val = stacks[org].pop().unwrap();
        //         stacks[dest].push(val)
        //     }
        // });
        .for_each(|(amount, org, dest)| {
            let size = stacks[org].len() - amount;
            let clone = stacks[org].clone();
            stacks[dest].extend_from_slice(&clone[size..]);
            stacks[org].truncate(size)
        });

    stacks.iter().for_each(|s| print!("{}", s.last().unwrap()));
    Ok(())
}
