import java.util.ArrayList;
import java.util.Collections;
import java.util.Scanner;

public final class HangmanUtils {

    // GAME STATE VARIABLES
    private static int attemptsLeft = 6;
    private static int correctGuesses = 0;
    private static String chosenWord = "";
    private static ArrayList<String> chosenWordCharacters = new ArrayList<>();
    private static ArrayList<String> guessedLetters = new ArrayList<>();
    private static Scanner reader = new Scanner(System.in);


    // GAME FLOW METHODS

    public static void playGame(String chosenWordInput) {
        chosenWord = chosenWordInput.toUpperCase();
        for (char c : chosenWord.toCharArray()) {
            chosenWordCharacters.add(Character.toString(c));
        }
        printLine("\nWELCOME TO HANGMAN ༼ つ ◕_◕ ༽つ\n");

        while (attemptsLeft != 0) {
            playRound();
            if (correctGuesses == chosenWord.length()) {
                printGameOver(true);
                break;
            }
        }

        if (attemptsLeft == 0) { printGameOver(false); }
        reader.close();
    }

    private static void playRound() {
        printWordProgress();
        printGuessedLetters();
        printLine("Guess Left: " + attemptsLeft);
        printGameState();
        String guess = readCharacter();
        printLine("\n             │\n             │\n             │\n             v");
        if (guessedLetters.contains(guess)) {
            printLine("\n~~ You've already guessed that you stupid fuck ~~\n");
            return;
        }
        guessedLetters.add(guess);
        Collections.sort(guessedLetters);

        if (chosenWordCharacters.contains(guess)) {
            printLine("\n~~ You son of a bitch, by god '" + guess + "' is in the word ~~\n");
            int numTimesGuessInWord = chosenWord.length() - chosenWord.replaceAll(guess,"").length();
            correctGuesses += numTimesGuessInWord;
        }
        else {
            attemptsLeft -= 1;
            printLine("\n~~ You absolute fucking idiot, '" + guess + "' isn't even close to being in the word ~~\n");
        }
    }

    private static String readCharacter() {
        String guess = "";

        while (guess.length() != 1) {
            System.out.print("What letter you finna guess?: ");
            guess = reader.nextLine();

            if (guess.length() == 0) {
                printLine("\n~~ You didn't enter anything fucking idiot what the fuck are you doing ~~\n");
            }
            else if (guess.length() > 1) {
                printLine("\n~~ You fucking dumbass you put in more than one guess fucking pay attention ~~\n");
            }
        }
        return guess.toUpperCase();
    }


    // PRINT GAME METHODS

    private static void printLine(String str) {
        System.out.println(str);
    }

    private static void printWordProgress() {
        String wordProgress = "Your word: ";
        for (String c : chosenWordCharacters) {
            if (guessedLetters.contains(c)) {
                wordProgress += c + "  ";
            }
            else {
                wordProgress += "_  ";
            }
        }
        printLine(wordProgress);
    }

    private static void printGuessedLetters() {
        String guessedLettersLine = "Guessed Letters: [";
        for (String c : guessedLetters) {
            guessedLettersLine = guessedLettersLine + " " + c;
        }
        printLine(guessedLettersLine + " ]");
    }

    private static void printGameOver(boolean win) {
        printLine("YOUR FINAL BOARD:");
        printGameState();
        printWordProgress();
        if (win) {
            printLine("\n~~ Holy fucking shit you did it you amazing motherfucker you did it, the word was indeed " + chosenWord + " ~~");
        }
        else {
            printLine("\n~~ What an absolute fucking failure, you are so fucking dumb. The word was " + chosenWord + " ~~");
        }
    }

    private static void printGameState() {
        String line1 = "* * * * * * * * * *\n";
        String line2 = "*   ┌────────┐    *\n";
        String line3 = "*   │        │    *\n" ;

        String line4A = "*   │        @    *\n";
        String line4B = "*   │             *\n";
        String line4 = (attemptsLeft < 6) ? line4A : line4B;

        String line5A = "*   │        │    *\n";
        String line5B = "*   │             *\n";
        String line5 = (attemptsLeft < 5) ? line5A : line5B;

        String line6;
        String line6A = "*   │       /│    *\n";
        String line6B = "*   │       /│\\   *\n";
        String line6C = "*   │             *\n";
        if (attemptsLeft == 3) { line6 = line6A; }
        else if (attemptsLeft < 3) { line6 = line6B; }
        else { line6 = line6C; }

        String line7;
        String line7A = "*   │       /     *\n";
        String line7B = "*   │       / \\   *\n";
        String line7C = "*   │             *\n";
        if (attemptsLeft == 1) { line7 = line7A; }
        else if (attemptsLeft < 1) { line7 = line7B; }
        else { line7 = line7C; }

        String line8 = "*   │             *\n";
        String line9 = "*   └─────────    *\n";

        String combined = "\n" + line1 + line2 + line3 + line4 + line5 + line6 + line7 + line8 + line9 + line1;
        printLine(combined);
    }
}
