use std::fs::File;
use std::io::Read;
fn main() -> Result<(), std::io::Error> {
    let mut file = match File::open("input.txt") {
        Ok(file) => file,
        Err(error) => panic!("Error opening the file {error}"),
    };
    let mut content = String::new();
    file.read_to_string(&mut content)?;
    let v: Vec<Vec<i32>> = content
        .split("\n\n")
        .map(|elf_bag| {
            elf_bag
                .split('\n')
                .map(|num| num.parse::<i32>().unwrap_or(0))
                .collect()
        })
        .collect();
    // collect::<Vec<&str>>();
    // let v2: Vec<Vec<&str>> = v.iter().map(|bag| bag.split('\n').collect::<Vec<&str>>()).collect();
    // println!("v: {v2:?}");
    // let v3: Vec<Vec<i32>> = v2.iter().map(|row|
    //                               row.iter().map(|num| {
    //                                   println!("num: {num}");
    //                                   match num.parse::<i32>() {
    //                                       Ok(number) => number,
    //                                       Err(_) => 0,
    //                                   }
    //                               }).collect::<Vec<i32>>()
    //                           ).collect();
    // // let result:i32 = v3.iter().map(|bag| bag.iter().sum()).max().unwrap();
    let result = v
        .iter()
        .map(|bag| bag.iter().sum::<i32>())
        .collect::<Vec<i32>>()
        .iter()
        .fold(vec![0, 0, 0], |mut acc, &num| {
            if num > acc[0] {
                acc[2] = acc[1];
                acc[1] = acc[0];
                acc[0] = num;
            } else if num > acc[1] {
                acc[2] = acc[1];
                acc[1] = num;
            } else if num > acc[2] {
                acc[2] = num;
            }
            acc
        })
        .iter()
        .sum::<i32>();
    // v.map(|bag| bag.split)
    println!("v: {v:?}");
    println!("{result:?}");

    Ok(())
}
