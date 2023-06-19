
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Random;
import java.util.Scanner;

//-----------------------------------------------------
//Assignment 1
//Question: Part 1 
//Written by: Vlad Tita 40209853
//-----------------------------------------------------
//This program creates and runs a Snakes and Ladders game in the terminal. To play simply follow the instructions!

public class LadderAndSnake {
	
	private final int ROWS = 10;
	private final int COLLUMNS = 10;
	private final int NUM_SNAKES = 8;
	private final int NUM_LADDERS = 9;
		
	private int[][] gameBoard;
	private int[][] snakes;
	private int[][] ladders;
	
	//This is a map of player positions
	Map<PlayGame, Integer> playerPositions;
		
	Scanner scan = new Scanner(System.in);
	public int numPlayers = 0;
		
	public int getNumPlayers(int numPlayers) {
		return numPlayers;
		
	}
	
	public LadderAndSnake(List<PlayGame> players) {
		 
		//This initializes the player positions
		this.playerPositions = new HashMap<PlayGame, Integer>();
		for (PlayGame player : players){
			this.playerPositions.put(player, 0);
		}

		//Sets up the rows and columns for the board
		gameBoard = new int[ROWS][COLLUMNS];
		for (int row = 0; row < ROWS; row++){
			for (int col = 0; col < COLLUMNS; col++){
				gameBoard[row][col] = row*ROWS + col + 1;
			}
		}
		//Calls the methods to set the snakes and the ladders
		setSnakes();
		setLadders();
	}
	//This method moves the player to the correct value depending on the roll and the snakes and ladders.
	public boolean movePlayer(PlayGame player, int number) {
		
		int position = playerPositions.get(player);
		position += number;
		
		//This first condition tells us that if the position is 100 the player wins.
		if(position == 100) {
			playerPositions.put(player, 100);
			return true;
		}
		//This one tells us that if the position is to exceed 100, the player must go back for the extra spaces rolled.
		else if (position > 100) {
			int extra = position - 100;
			playerPositions.put(player, 100-extra);
			return false;
		}
		//This part checks if the player is on a snake or a ladder and moves him accordingly
		else {
			for (int i = 0; i < NUM_SNAKES; i++){
				if (snakes[i][0] == position){
					position = snakes[i][1];
					playerPositions.put(player, position);
					
					System.out.println("Oh no! " + player + " slips on a snake from " + snakes[i][0] + " to " + snakes[i][1]);

					return false;
				}
			}

			for (int i = 0; i < NUM_LADDERS; i++){
				if (ladders[i][0] == position){
					position = ladders[i][1];
					playerPositions.put(player, position);

					System.out.println("Oh yeah! " + player + " climbs a ladder from " + ladders[i][0] + " to " + ladders[i][1]);
					
					return false;
				}
			}
			//This part moves the player normally if nothing else is happening
			playerPositions.put(player, position);
			return false;
		}
	}
	//This method places all the snakes on the board
	private void setSnakes() {
		snakes = new int[NUM_SNAKES][2];

		snakes[0][0] = 16;
		snakes[0][1] = 6;
		snakes[1][0] = 48;
		snakes[1][1] = 30;
		snakes[2][0] = 62;
		snakes[2][1] = 19;
		snakes[3][0] = 64;
		snakes[3][1] = 60;
		snakes[4][0] = 93;
		snakes[4][1] = 68;
		snakes[5][0] = 95;
		snakes[5][1] = 24;
		snakes[6][0] = 97;
		snakes[6][1] = 76;
		snakes[7][0] = 98;
		snakes[7][1] = 78;
	}
	//This method places all the ladders on the board
	private void setLadders(){
		ladders = new int[NUM_LADDERS][2];

		ladders[0][0] = 1;
		ladders[0][1] = 38;
		ladders[1][0] = 9;
		ladders[1][1] = 31;
		ladders[2][0] = 4;
		ladders[2][1] = 14;
		ladders[3][0] = 21;
		ladders[3][1] = 42;
		ladders[4][0] = 28;
		ladders[4][1] = 84;
		ladders[5][0] = 36;
		ladders[5][1] = 44;
		ladders[6][0] = 51;
		ladders[6][1] = 67;
		ladders[7][0] = 71;
		ladders[7][1] = 91;
		ladders[8][0] = 80;
		ladders[8][1] = 100;
	}
	//This method makes a the board visible to us so we can keep track of the game.
	public String toString() {
		StringBuilder sb = new StringBuilder();
		boolean oddRow = true;
		//We use a string builder to make the board since it is easier to create and modify the string with it.
		//The following loop makes sure each row is read in the right order since each row switches from left to right, to right to left.
		for (int row = ROWS-1; row >= 0; row--){
			for (int col = 0; col < COLLUMNS; col++){
				//The following checks are here to check if a player occupies a location on the board and if so it prints the player instead of the location.
				if (oddRow){
					String pl = "";
					boolean occupied = false;
					for (PlayGame temp : playerPositions.keySet()){
						if (playerPositions.get(temp) == gameBoard[row][COLLUMNS-1-col]){
							occupied = true;
							pl += temp + " ";
						}
					}
					
					if (occupied){
						pl += "\t";
						sb.append(pl);
					} else {
						sb.append(gameBoard[row][COLLUMNS-1-col] + "\t");						
					}
				} else {
					boolean occupied = false;
					String pl = "";
					for (PlayGame temp : playerPositions.keySet()){
						if (playerPositions.get(temp) == gameBoard[row][col]){
							occupied = true;
							pl += (temp + " ");
						}
					}
					
					if (occupied){
						pl += "\t";
						sb.append(pl);	
					} else {
						sb.append(gameBoard[row][col] + "\t");
					}
				}
			} 
			oddRow = !oddRow;
			sb.append("\n");
		}
		sb.append("\n");

		return sb.toString();
	}
	//This method rolls a dice and give us a number
	public static int flipDice() {
		Random random = new Random();
		return random.nextInt(6)+1;
	
	}
	
	
	
	public void play() {
	
		
	}
	
}
