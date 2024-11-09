use std::fs::File;
use std::io::Read;

fn main() -> Result<(), std::io::Error> {
    let mut file = File::open("input.txt")?;
    let mut content = String::new();
    file.read_to_string(&mut content)?;
    // let mut found_chars = HashSet::new();
    for (a, b) in content.as_bytes().windows(14).enumerate() {
        let mut found = true;
        for i in 0..14 {
            found = true;
            for j in 0..14 {
                if i == j {
                    continue;
                }
                if b[i] == b[j] {
                    found = false;
                    break;
                }
            }
            if !found {
                break;
            }
        }
        if found {
            println!("{}", a + 14);
            return Ok(());
        }
    }
    // println!("{ch:?}")
    // if found_chars.contains(&ch) {
    //     found = false;
    //     break;
    // }
    // found_chars.insert(ch);
    // }
    // if found {
    //     println!("{}", i+14);
    //     break;
    // }
    Ok(())
}
