Student: Barus Catalin-Stefan
Group: 321 CD

***** OOP Project Phase 2 *****

Disclaimer: If you see spacing issues, open the readme in Sublime Text or equivalent program.

** Design Patterns **

For the main implementation, I had created objects for the consumer and the
distributor using a Singleton design pattern (with an eager initiation), since
they will most definetely be used for the ArrayLists containing the data from
the input files.

Additionaly, I had implemented the base for the Strategy design pattern which is
used to decide which strategy is required when choosing the right producer for
each distributor


* The implementation *

For solving this homework, I had created three core packages: "fileloader", crucial for reading and parsing the data from the json files, "humaninstances", which contains the key classes for the main implementation as well as "displayinstances", which contains classes used for formatting the output json files adequately.

Their structure is as follows:

* humaninstances - Package that contains the main objects used for the 							   implementation of the game.

	* Contract - Class that contains the key data for a single contract. It is mainly used for storing the contracts of a single dstributor.

	* InstanceConsumer - Class that contains the key data for a consumer.

	* InstanceDistributor - Class that contains the key data for a distributor.

	* InstanceProducer- Class that contains the key data for a distributor.

	* MonthlyTurnUpdates - Class that contains the key data for the montly
						   updates per turn for a consumer and a distributor.

	For this class, the main monthly updates are stored inside an ArrayList for
	the consumer, distributor and producer changes.

* displayinstances - Package used primarily for formatting the data so it could
					 look as intened in the ref files.

	* FinalConsumers, FinalContracts, FinalDistributors, FinalPrint 

	- Classes that contain the data to be formatted for the json
	output file.

	- FinalPrint is the class where the final output will be stored and used
	  with objectmapper in main to display the required data in the json files.

* strategies - Package used for the Strategy design pattern

	* EnergyStrategy - Interface used for the Strategy design pattern

	* EnergyChoiceStrategyType - Enum used for distributors to choose their
								 producers

	* Green - Class that implements the EnergyStrategy interface and applies the
	          Green strategy

	* Price - Class that implements the EnergyStrategy interface and applies the
	          Price strategy

	* Quantity - Class that implements the EnergyStrategy interface and applies 			 the Quantity strategy

* fileloader - Package used for parsing the data of the input json files.

	* Data - Class used for parsing the read data into multiple ArrayLists for 
			 each important object.

	* DataLoader - Class used for reading the json data and transmitting the read
				   data into multiple arraylists in data.


* Main - this is where it all comes together.

Initially, we will be using the Singleton design pattern to create instances of 
a consumer and a distributor since we know that they will be used when creating
the lists containing the data parsed from the input files.

After the initiation part, a separate implementation will be dedicated to the
first round of the game, or to be more precise, the round 0. After that, the main
implementation will begin the for with the number of turns.




















