import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;
//-----------------------------------------------------
//Assignment 1
//Question: Part 2 
//Written by: Vlad Tita 40209853
//-----------------------------------------------------
//This class is our driver class where we will run the game
public class PlaySnakesAndLadders {

	//First we output a welcome message
	public static void main(String[] args) {
		System.out.println("Welcome to my Snakes and Ladders game!");
		System.out.println("Created by Vlad Tita");
		System.out.println();
		//Then we will ask the player to output the number of players
		Scanner scan = new Scanner (System.in);
		System.out.println("Please enter the number of players : (between 2-4)");
		int numPlayers = scan.nextInt();
		//This loop is here to make sure the user chooses 2-4 players. If not it gives the user 3 more chances to try again before terminating the program after the 4th attempt.
		for (int index = 1; index < 5; index ++) {
			if (numPlayers <= 1 || numPlayers >4 && index < 4) {
				System.out.println("Bad Attempt " + index + " - Invalid # of players. Please enter a # between 2 and 4 inclusively:");
				numPlayers = scan.nextInt();
			}
			else if (index == 4) {
				System.out.println("Bad Attempt 4! You have exhausted all your chances. Program will terminate!");
				System.exit(0);
			}
			else {
				System.out.println("All good!");
				break;
			}

		}
		//This part initializes the players
		List<PlayGame> players = new ArrayList<PlayGame>();
		
		for (int i = 0; i < numPlayers; i++){
			PlayGame player = new PlayGame("P" + i);
			players.add(player);
		}
		//This line initializes the board.
		LadderAndSnake board = new LadderAndSnake(players);
		
		//This is a loop that will go on until a player reaches the end.
		boolean done = false;
		int playerIdx = 0;
		while (!done){
			PlayGame currPlayer = players.get(playerIdx);
			//It allows each player to take turns rolling the dice and moving along the board.
			int roll = currPlayer.takeTurn();
			
			//This updates the board.
			done = board.movePlayer(currPlayer, roll);
			
			//This prints out the board.
			System.out.println(board);
			System.out.println("-----------------------\n");
			
			//This ends the game if done.
			if (done){
				System.out.println(currPlayer + " wins");
			}
			//This sets up for the next player.
			playerIdx++;
			if (playerIdx == numPlayers){
				playerIdx = 0;
			}
		}
		
	}

}
