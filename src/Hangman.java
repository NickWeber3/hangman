import java.io.File;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;

import java.util.List;
import java.util.Random;

public class Hangman {
    public static void main(String[] args) throws IOException {
        boolean playAgain = true;
        while (playAgain) {
            // Open text file containing words, parse into array
            Path filePath = new File("src/HangmanWords.txt").toPath();
            List<String> stringList = Files.readAllLines(filePath);
            String[] stringArray = stringList.toArray(new String[]{});

            // Generate random word from word list
            Random random = new Random();
            int randomIndex = random.nextInt(stringArray.length);
            String chosenWord = stringArray[randomIndex];
            playAgain = HangmanUtils.playGame(chosenWord);
        }
    }
}