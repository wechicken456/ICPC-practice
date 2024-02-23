/**
 * This solution is O(k*n^4) for n words and maximum word length k.
 * It is expected to receive the TLE verdict.
 *
 * @author Finn Lidbetter
 */

use std::io::BufRead;

fn main() {
    let reader = std::io::stdin();

    let mut lines_iter = reader.lock().lines();
    let first_line = lines_iter.next().unwrap().unwrap();
    let n = first_line.parse().unwrap();
    let words: Vec<Vec<u8>> = lines_iter.map(
        |line| line.unwrap().into_bytes()
    ).collect();
    let mut pairs_count = 0;
    for index_1 in 0..n {
        let word_1 = &words[index_1];
        for index_2 in index_1+1..n {
            let word_2 = &words[index_2];
            if word_2.len() != word_1.len() {
                continue;
            }
            let mut offset: Option<usize> = None;
            for (i, ch) in word_1.iter().enumerate() {
                if i == word_1.len() - 1 {
                    break;
                }
                if &word_2[i] != ch {
                    if word_2[i+1] != word_1[i+1] {
                        offset = Some(i);
                        break;
                    } else {
                        break;
                    }
                }
            }
            let is_clue = match offset {
                Some(offset_val) => {
                    let prefix_1 = &word_1[0..offset_val];
                    let prefix_2 = &word_2[0..offset_val];
                    let suffix_1 = &word_1[offset_val+2..];
                    let suffix_2 = &word_2[offset_val+2..];
                    prefix_1 == prefix_2 && suffix_1 == suffix_2
                },
                None => false,
            };
            if !is_clue {
                continue;
            }
            let offset = offset.unwrap();
            let clue_1 = &word_1[offset..offset+2];
            let clue_2 = &word_2[offset..offset+2];
            let mut other_match = false;
            for index_3 in 0..n {
                if index_3 == index_1 || index_3 == index_2 {
                    continue;
                }
                let word_3 = &words[index_3];
                if word_3.len() != word_1.len() {
                    continue;
                }
                let prefix_3 = &word_3[0..offset];
                let middle = &word_3[offset..offset+2];
                let suffix_3 = &word_3[offset+2..];
                let other_middle = match middle {
                    _ if middle == clue_1 => Some(clue_2),
                    _ if middle == clue_2 => Some(clue_1),
                    _ => None,
                };
                if other_middle.is_none() {
                    continue;
                }
                for index_4 in index_3+1..n {
                    if index_4 == index_1 || index_4 == index_2 {
                        continue;
                    }
                    let word_4 = &words[index_4];
                    if word_4.len() != word_1.len() {
                        continue;
                    }
                    let target = [prefix_3, other_middle.unwrap(), suffix_3].concat();
                    if word_4 == &target {
                        other_match = true;
                        break;
                    }
                }
                if other_match {
                    break;
                }
            }
            if !other_match {
                pairs_count += 1;
            }
        }
    }
    println!("{}", pairs_count);
}
