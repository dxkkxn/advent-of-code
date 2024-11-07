use std::fs::File;
use std::io::Read;

use std::collections::HashSet;

fn main() -> Result<(), std::io::Error> {
    let mut file = File::open("input.txt")?;
    let mut content = String::new();
    file.read_to_string(&mut content)?;
    let result: u32 = content
        .lines()
        .map(|line| {
            let (first, second) = line.split_at(line.len() / 2);
            let mut map_first: HashSet<char> = HashSet::new();
            first.chars().for_each(|ch| {
                if !map_first.contains(&ch) {
                    map_first.insert(ch);
                }
            });

            let mut map_second: HashSet<char> = HashSet::new();
            second.chars().for_each(|ch| {
                if !map_second.contains(&ch) {
                    map_second.insert(ch);
                }
            });
            map_first
                .intersection(&map_second)
                .map(|ch| match ch {
                    'a'..='z' => *ch as u32 - 96,
                    'A'..='Z' => *ch as u32 - 38,
                    _ => todo!(),
                })
                .sum::<u32>()
        })
        .sum();
    println!("{result:?}");

    let result_part_two: u32 = content
        .lines()
        .collect::<Vec<&str>>()
        .chunks(3)
        .map(|a| {
            let res: Vec<HashSet<char>> = a.iter().map(|rs| rs.chars().collect()).collect();
            res[0].intersection(&res[1])
                .filter(|e| res[2].contains(e))
                .map(|ch| match ch {
                    'a'..='z' => *ch as u32 - 96,
                    'A'..='Z' => *ch as u32 - 38,
                    _ => todo!(),
                })
                .sum::<u32>()
        })
        .sum();
    println!("{result_part_two:?}");

    Ok(())
}
