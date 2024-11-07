use std::collections::HashMap;
use std::fs::File;
use std::io::Read;

fn main() -> Result<(), std::io::Error> {
    let mut file = File::open("input.txt")?;
    let mut content = String::new();
    file.read_to_string(&mut content)?;
    // win 6, draw 3, lose 0
    // A X Rock 1
    // B Y paper 2
    // C Z sicciosrs 3
    // X lose, Y draw, Z win
    let _outcomes = HashMap::from([
        ("A X", 4),
        ("A Y", 8),
        ("A Z", 3),
        ("B X", 1),
        ("B Y", 5),
        ("B Z", 9),
        ("C X", 7),
        ("C Y", 2),
        ("C Z", 6),
    ]);

    let outcomes_part_two = HashMap::from([
        ("A X", 3),
        ("A Y", 4),
        ("A Z", 8),
        ("B X", 1),
        ("B Y", 5),
        ("B Z", 9),
        ("C X", 2),
        ("C Y", 6),
        ("C Z", 7),
    ]);
    let res = content.split('\n').fold(0, |mut score, game| {
        score += outcomes_part_two.get(game).unwrap_or(&0);
        println!("here:{game}, {score}");
        score
    });
    println!("{res}");
    Ok(())
}
