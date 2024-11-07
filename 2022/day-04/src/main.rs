use std::fs::File;
use std::io::Read;
use std::fmt;


struct Interval {
    start: u32,
    end: u32,
}

impl fmt::Debug for Interval {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "({}-{})", self.start, self.end)
    }
}

fn full_collision(first: &Interval, second: &Interval) -> bool {
    (first.start <= second.start && second.end <= first.end) ||
    (second.start <= first.start && first.end <= second.end)
}

fn overlap(first: &Interval, second: &Interval) -> bool {
    (second.start <= first.start && first.start <= second.end) ||
    (first.start <= second.start && second.start <= first.end)
}

fn main() -> Result<(), std::io::Error> {
    let mut file = File::open("input.txt")?;
    let mut content = String::new();
    file.read_to_string(&mut content)?;
    let result = content.lines().map(|line| {
        let v: Vec<Interval> = line.split(',').map(|itv| {
            let (s, e) = itv.split_once('-').unwrap();
            Interval {
                start: s.parse::<u32>().unwrap(),
                end: e.parse::<u32>().unwrap(),
            }
        }).collect();
        if overlap(&v[0], &v[1]) {
            1
        } else {
            0
        }
    }).sum::<u32>();
    println!("{result}");
    Ok(())
}
