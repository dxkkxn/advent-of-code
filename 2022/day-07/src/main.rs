use std::cell::RefCell;
use std::rc::Rc;
use std::{fs::File, io::Read};

enum Element<'a> {
    MyFile(Rc<RefCell<MyFile>>),
    Dir(Rc<RefCell<Dir<'a>>>),
}

struct MyFile {
    size: u32,
}

struct Dir<'a> {
    name: &'a str,
    elements: Vec<Element<'a>>,
}

impl<'a> Dir<'a> {
    fn new(name: &'a str) -> Self {
        Dir {
            name,
            elements: Vec::new(),
        }
    }
}

fn compute_size(current_dir: Rc<RefCell<Dir>>) -> (u32, u32) {
    let mut total_sum: u32 = 0;
    let mut lower_than_100_000: u32 = 0;
    for e in current_dir.borrow().elements.iter() {
        match e {
            Element::MyFile(ref file) => total_sum += file.borrow().size,
            Element::Dir(ref dir) => {
                let (dir_size, lower_size) = compute_size(dir.clone());
                println!("{}: {dir_size} {lower_size}", dir.borrow().name);
                lower_than_100_000 += lower_size;
                total_sum += dir_size;
            }
        }
    }
    if total_sum < 100_000 {
        lower_than_100_000 += total_sum;
    }
    (total_sum, lower_than_100_000)
}

fn find_smaller_removable(current_dir: Rc<RefCell<Dir>>, ns: u32) -> (u32, Option<u32>) {
    let mut total_sum: u32 = 0;
    let mut smaller_found: Option<u32> = None;
    for e in current_dir.borrow().elements.iter() {
        match e {
            Element::MyFile(ref file) => total_sum += file.borrow().size,
            Element::Dir(ref dir) => {
                let (dir_size, smaller) = find_smaller_removable(dir.clone(), ns);
                println!("{}: {dir_size} ", dir.borrow().name);
                match smaller {
                    Some(value) => {
                        if smaller_found.is_none() || smaller_found.unwrap() > value {
                            smaller_found = Some(value);
                        }
                    }
                    None => (),
                }
                total_sum += dir_size;
            }
        }
    }
    if total_sum > ns
        && (smaller_found.is_none()
            || (smaller_found.is_some() && total_sum < smaller_found.unwrap()))
    {
        (total_sum, Some(total_sum))
    } else {
        (total_sum, smaller_found)
    }
}

fn main() -> Result<(), std::io::Error> {
    let mut file = File::open("input.txt")?;
    let mut content = String::new();
    file.read_to_string(&mut content)?;
    let root_dir = Dir::new("/");
    let root = Rc::new(RefCell::new(root_dir));
    let mut stack: Vec<Rc<RefCell<Dir>>> = vec![root.clone()];
    let mut current = root.clone();
    for line in content.lines().skip(1) {
        if line == "$ ls" {
            continue;
        }
        let (mut first, mut second) = line.split_once(' ').unwrap();
        if first == "dir" {
            current
                .borrow_mut()
                .elements
                .push(Element::Dir(Rc::new(RefCell::new(Dir::new(second)))));
        } else if let Ok(val) = first.parse::<u32>() {
            current
                .borrow_mut()
                .elements
                .push(Element::MyFile(Rc::new(RefCell::new(MyFile { size: val }))));
        } else if first == "$" {
            (first, second) = second.split_once(' ').unwrap();
            if first == "cd" && second == ".." {
                current = stack.pop().unwrap();
            } else if first == "cd" {
                let dir = {
                    let borrowed = current.borrow();
                    let x = borrowed
                        .elements
                        .iter()
                        .find(|element| match element {
                            Element::Dir(dir) => dir.borrow().name == second,
                            _ => false,
                        })
                        .unwrap();
                    let gdir = match *x {
                        Element::Dir(ref dir) => dir,
                        _ => todo!(),
                    };
                    gdir.clone()
                };
                // println!("name: {}", dir.name);
                stack.push(current.clone());
                current = dir;
            }
        }
    }
    for e in &root.borrow().elements {
        match e {
            Element::MyFile(file) => println!("{}", file.borrow().size),
            Element::Dir(dir) => println!("{}", dir.borrow().name),
        }
        println!()
    }
    let (root_size, smaller) = compute_size(root.clone());
    println!("{:?}", smaller);
    // part 2
    let needed_space = 30_000_000 - (70_000_000 - root_size);
    println!("{needed_space} {:?}", find_smaller_removable(root.clone(), needed_space));


    Ok(())
}
