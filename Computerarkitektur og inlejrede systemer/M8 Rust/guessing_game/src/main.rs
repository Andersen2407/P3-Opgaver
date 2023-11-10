use std::{io, cmp::Ordering};        // Import io

// Puts Rng trait in scope so we can use its functions
use rand::Rng;      // https://docs.rs/rand/0.8.5/rand/trait.Rng.html

fn main() {
    // Generate random number. Rust automatically makes a number into an unsigned 32-bit
    let secret_number = rand::thread_rng().gen_range(1..=100);

    loop {      // Grant multiple guesses
        println!("Guess the number!");
        let mut guess = String::new();  // Mutable variable String

        //io::stdin() returns an instance of std::io::Stdin, which is a type that represents a handle to the standard input for the terminal
        // Call read_line() and pass &mut guess, which it will copy the input over into
            // guess needs to be mutable, so read_line() can change its contents
            // "&" indicates that guess is passed by reference (not value)
            // Since references also are immutable by default, we need to pass &mut to make it mutable
            // read_line() returns an "enum", either Ok or Err
                // .expect handles a potential failure
        io::stdin().read_line(&mut guess).expect("Failed to read line");
        
        let guess = guess.trim();   // Remove newline (from input)

        // {} in a string work like a formatted string in python
        // println!("You guessed: {guess}");

        // Convert guess into int
        // Uses "shadowing", which lets us reuse the guess variable (essentially overwriting it)
                        // match, which grants different behaviour depending on parse()
                                  // trim() removes whitespaces and newlines
                                         // parse() parses the string into the requested type
        let guess: u32 = match guess.trim().parse() {
            Ok(num) => num,
            Err(_) => continue,
        };

        // match works like a switch-case
        // guess.cmp returns an "Ordering" enum
        match guess.cmp(&secret_number) {
            Ordering::Less => println!("Too small"),
            Ordering::Greater => println!("Too big"),
            Ordering::Equal => {
                println!("You win");
                break;
            }
        }
    }
}

