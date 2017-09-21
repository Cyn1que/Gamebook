# Gamebook

This is my semestral project for BI-PA2 module. I was assigned to created CLI based dungeon crawler game written in C++. The project is modular in
sense that you can create your own worlds to be played within the game, assuming you can obey the basic data structure (described below).

## Getting Started

Simply clone the project. If you have VS2017, compilation shouldn't prove difficult - just open the Gamebook.sln solution file and go from there.
If you are sporting Linux, there is Makefile included in the Gamebook/Linux folder for your convenience. Example usage:

```
make compile
make run
```

### Prerequisites

C++ compiler compliant with C++14 standard.

### Code documentation

Code is documented with brief descriptions. If you wish to generate Doxy documentation, there is Doxyfile packed in Gamebook/Linux folder. Run it using:

```
make doc
```

## Game manual

Upon loading the game, you are presented with menu where you can select one of five options by typing 1-5 and submitting your choice.
You can return to this menu at any time by typing **menu** command.
Whether you decide to start a new game or load old one, you will be asked to select World File. Test world comes packed with this
repository - you can find it within TestData folder. If you wanna use it, input value 'TestData/TestWorld.json' into prompt.
Saving the game will create another type of *.json file that you will be asked to locate when loading old save.
The path to both of these files starts within the folder where compiled binary resides.

Rest of the game is controlled by selecting the enumerated option and submitting it. Last option is to open an inventory by typing
**inv** command and submitting.

## World Data structure

There is an example WorldFile in TestData folder. The structure looks like this:

```
{	"worldName": "Flight from the Dark",
	"worldDescription": "In the northern land of Sommerlund, it has been the custom for many centuries to send the children of the Warrior Lords to the monastery of Kai. There they are taught the skills and disciplines of their noble fathers.\nThe Kai monks are masters of their art, and the children in their charge love and respect them in spite of the hardships of their training. For one day when they have finally learnt the secret skills of the Kai, they will return to their homes equipped in mind and body to defend themselves against the constant threat of war from the Darklords of the west.\nIn olden times, during the Age of the Black Moon, the Darklords waged war on Sommerlund. The conflict was a long and bitter trial of strength that ended in victory for the Sommlending at the great battle of Maakengorge. King Ulnar and the allies of Durenor broke the Darklord armies at the pass of Moytura and forced them back into the bottomless abyss of Maakengorge. Vashna, mightiest of the Darklords, was slain upon the sword of King Ulnar, called Sommerswerd, the sword of the sun. Since that age, the Darklords have vowed vengeance upon Sommerlund and the House of Ulnar.\nNow it is in the morning of the feast of Fehmarn, when all of the Kai Lords are present at the monastery for the celebrations. Suddenly a great black cloud comes from out of the western skies. So many are the numbers of the black-winged beasts that fill the sky, that the sun is completely hidden. The Darklords, ancient enemy of the Sommlending are attacking. War has begun.\nOn this fateful morning, you, Silent Wolf (the name given to you by the Kai) have been sent to collect firewood in the forest as a punishment for your inattention in class. As you are preparing to return, you see to your horror a vast cloud of black leathery creatures swoop down and engulf the monastery.\nDropping the wood, you race to the battle that has already begun. But in the unnatural dark, you stumble and strike your head on a low tree branch. As you lose consciousness, the last thing that you see in the poor light are the walls of the monastery crashing to the ground.\nMany hours pass before you awake. With tears in your eyes you now survey the scene of destruction. Raising your face to the clear sky, you swear vengeance on the Darklords for the massacre of the Kai warriors, and with a sudden flash of realization you know what you must do. You must set off on a perilous journey to the capital city to warn the King of the terrible threat that now faces his people. For you are now the last of the Kai - you are now the Lone Wolf.\n",
	  "locations": [
		{
		  "ID": 1,
		  "description": "At the foot of the hill, the path splits into two directions, both leading into a large wood.\n",
		  "connections": [
			{
			  "description": "Take the right path into the wood.",
			  "destinationID": 2
			},
			{
			  "description": "Turn left and run up the hill.",
			  "destinationID": 2
			}
		  ],
		  "interactions": [
			{
			  "type": "enemy",
			  "name": "Kraan",
			  "stats": {
				"damage": 10,
				"health": 25,
				"missChance": 8,
				"speed": 7
			  },
			  "items": [
				{
				  "category": 3,
				  "name": "Dagger",
				  "stats": {
					"accuracy": 0,
					"damage": 4,
					"health": 1,
					"speed": 0
				  }
				}
			  ]
			}
		  ]
		},
		{
		  "ID": 2,
		  "description": "You fall to your death.",
		  "connections": [],
		  "interactions": []
		},
		{
		  "ID": 3,
		  "description": "End of the road.",
		  "connections": [],
		  "interactions": []
		}
	  ]
}

I believe the structure is quite self-explenatory.
```
