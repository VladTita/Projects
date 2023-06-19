import java.util.Scanner;

public class PlayGame {

	private String name = "";
	
	//Setter
	public PlayGame(String name) {
		this.name = name;
	}
	
	//This method plays out a players turn.
	public int takeTurn() {
		//This part prompts the user for a roll
		Scanner scan = new Scanner(System.in);
		System.out.println(name + "'s turn: ");
		String input = scan.nextLine();
		
		//This part translates whatever input and a numeric value from 1 to 9.
		int val = 0;
		for (int i = 0; i < input.length(); i++){
			val+= input.charAt(i);
		}
		val = val % 10;
		if (val == 0){
			val = 1;
		}
		
		//This part throws away the next random values for "val"
		for (int idx = 0; idx < val; idx++){
			 LadderAndSnake.flipDice();
		}
		//This rolls the dice
		int roll = LadderAndSnake.flipDice();
		System.out.println(name + " rolled " + roll);
		return roll;
	}
	//Getter
	public String toString() {
		return name;
	}
	
	
	
	
	
}

