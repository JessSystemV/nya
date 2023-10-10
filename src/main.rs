use std::{
    env::args,
    io::{stdout, Write},
    thread,
    time::{Duration, SystemTime},
};

const NYA_AMOUNT: usize = 8; // must be power of 2
const NYAS: [&str; NYA_AMOUNT] = [
    "nya ",
    "nya~ ",
    "mew ",
    "meow ",
    "mrrp ",
    ":3 ",
    "meowmeow ",
    "mow ",
];

fn rand<const MAX: usize>(state: &mut u64) -> usize {
    let x = *state;
    *state = (x >> 8) + (x << 8);
    x as usize & (MAX - 1)
}

fn rand_merge(state: &mut u64, other: u64) {
    let s = *state;
    *state = (s << (s & 0b111)).wrapping_add(s >> (s & 0b111)) ^ other;
}

fn main() {
    let arg: u64 = args()
        .skip(1)
        .next()
        .expect("Hint: try actually telling me how much i should nya")
        .parse()
        .unwrap();
    let mut state = arg as u64;
    for _ in 0..100 {
        rand_merge(
            &mut state,
            SystemTime::UNIX_EPOCH.elapsed().unwrap().as_nanos() as u64,
        );
        thread::sleep(Duration::from_micros(1));
    }
    println!("Random state: {state:016x}");
    let mut stdout = stdout().lock();
    let mut gen = 0;
    let mut buf = [0; 16384];
    while gen < arg {
        let mut n = 0;
        while gen < arg && n < 16370 {
            let i = rand::<NYA_AMOUNT>(&mut state);
            let nya = NYAS[i];
            let nyalen = nya.len();
            buf[n..n + nyalen].copy_from_slice(nya.as_bytes());
            n += nyalen;
            gen += 1;
        }
        stdout.write_all(&buf[..n]).unwrap();
    }
}
