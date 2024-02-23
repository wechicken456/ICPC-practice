/**
 * Consider each pair of words and check if they differ in exactly two
 * consecutive characters. If they do, then we have a potential clue:
 *   ..AB/CD..
 * Iterate over the words to find some other word that could match either
 *   ..AB.. or ..CD..
 * If we find a match, then this uniquely determines a fourth word that
 * could be valid for the clue. E.g., if we had a match against ..AB..
 * with WXABYZ, then the fourth word would be WXCDYZ. So check for the
 * existence of this word.
 *
 * @author Finn Lidbetter
 */

val WORD_LEN_MAX = 50

fun main(args: Array<String>) {
/***** RSR REPLACED FOLLOWING LINES:
    var n = readln().toInt()
    var words = Array<String>(n){ _ -> readln() }
*******/
    var temp = readLine()?:""
    var n = temp.toInt()
    var words = Array<String>(n){ _ -> readLine()?:"" }

    var wordSets = Array<HashSet<String>>(WORD_LEN_MAX + 1) { _ -> HashSet<String>() }
    for (word in words) {
        wordSets.get(word.length).add(word)
    }
    var pairsCount = 0
    for (i in words.indices) {
        val word1 = words[i]
        val wordLen = word1.length
        for (j in i+1..n-1) {
            val word2 = words[j]
            if (word2.length != wordLen) {
                continue
            }
            val matches = IntArray(wordLen) {
                index -> if (word1[index] == word2[index]) 1 else 0
            }
            val numMatches = matches.sum()
            if (numMatches != wordLen - 2) {
                continue
            }
            var goodPair = false
            for (offset in 0..wordLen-2) {
                if (matches[offset] + matches[offset+1] == 0) {
                    goodPair = true
                    for (k in 0..n-1) {
                        if (k == i || k == j) {
                            continue
                        }
                        val word3 = words[k]
                        if (word3.length != wordLen) {
                            continue
                        }
                        var clueMatch = false
                        var otherClue = "";
                        if (substringMatch(word1, word3, offset, 2)) {
                            clueMatch = true
                            otherClue = word2.substring(offset, offset + 2)
                        }
                        else if (substringMatch(word2, word3, offset, 2)) {
                            clueMatch = true
                            otherClue = word1.substring(offset, offset + 2)
                        }
                        if (clueMatch) {
                            var sb = StringBuilder()
                            sb.append(word3.substring(0, offset))
                            sb.append(otherClue)
                            sb.append(word3.substring(offset + 2, wordLen))
                            val word4 = sb.toString()
                            if (wordSets.get(wordLen).contains(word4)) {
                                goodPair = false
                                break
                            }
                        }
                    }
                    break
                }
            }
            if (goodPair) {
                pairsCount++
            }
        }
    }
    println(pairsCount)
}
fun substringMatch(s1: String, s2: String, lo: Int, len: Int): Boolean {
    for (index in lo..lo+len-1) {
        if (s1[index]!=s2[index]) {
            return false
        }
    }
    return true
}
