Student: Barus Catalin-Stefan
Group: 321 CD

***** OOP Homework 1 *****

Disclaimer: If you see spacing issues, open the readme in Sublime Text or equivalent program.

** Design Idea **

* The beginning *

The implementation of the core program actually started with a difficult decision, as there were two ways to code this homework, from my perspective. Firstly, we were already given enough classes to work with for users, movies, tv series, actors and commands, so we could simply use them and create other classes for the different functions that were required. Secondly, we could "copy" (for the most part) those classes into new ones to assure that the provided implementation of parsing the JSON files is not broken. The second idea is the one I chose, primarily for safety reasons as well as the fact that I added more fields than were initially provided in the original classes.

* The actual implementation *

For solving this homework, I had created two core packages : "corecomponents" and "corefunctions", both curcial for simplifying the solution to the problems encountered and assuring the modularity of the code.

Their structure is as follows:

* corecomponents - Package that contains modified copies to the ones provided 				 	 for users, movies, tv series, actors and commands.

	* CoreAction - Class that contains data corresponding to the given 					   commands by a user, parsed from the JSON files. It keeps 			   the sturcture of the ActionInputData class.

	* CoreActor - Class that contains data corresponding to the actors. It 				  keeps the sturcture of the ActorInputData class. 

	* CoreMovie - Class that contains data corresponding to the movies. Its 			  structure has been heavily modified with most data coming 			  from the ShowInput class. Additionally, a field for rating 			   was added, since the original classes did not have one.

	* CoreSeries - Class that contains data corresponding to the tv series. 			   Its structure has been heavily modified with most data 				   coming from the ShowInput class. Additionally, a field for 				 rating was added, since the original classes did not have 				   one.

	* CoreUsers - Class that contains data corresponding to the users. It 				  keeps the sturcture of the UserInputData class.


* corefunctions - Package that implements most of the required commands from a 					 user, using multiple classes.

	* CoreCommands - Class that implements the 3 core commands a user can 					 give: favourite, view and rating.

	For this class there is, for the most part, a single function for each command with the exception of the rating command where the implementation has been broken down into multiple functions, one that takes care of the rating for the movies, since it's easier to implement, and 3 for a tv series, one that checks if a perticular season has been rated or not, one that finds the average rating of a series based on the individual ratings of a each season and one that adds this final rating in an ArrayList for a tv series' ratings. Additionally, an utility function that checks if a video is in an user's history or not was created.


	* CoreLaunch - Class that initializes multiple ArrayLists for the users, 				movies, tv series, actors and commands


	* CoreQueries - Class that contains utility functions for implementing the 				   "query" command.

	The main strategy for implementing this command was to split the functions into two for each type of video (movie or tv series), so 4 functions in total. For the sake of efficiency, I will only describe the functions for the movies since they are practically the same, and address the differences for the tv series as they arise.

	For the movies, there is a function that sorts the movies based on the number of appearances in users' lists of favourite movies. For this, we have to traverse the movie list and the list of favourite movies for each user and increment a counter when we find a match in both lists. For each movie, this counter will determine the number of appearences everywhere, so we will add this movie as well as its occurences in a map. Additionally, we will also take into account if the filters given by the user can be applied or not. For the tv series the process is identical with the execption that we have to traverse the tv series list.

	There is also a function that sorts the movies based on their duration. For this, we have to yet again traverse the movie list and retain the duration for each movie. Then, after checking if the filters can also be applied, we will put the title of the movie as well as the duration in a hasmap, to sort them accordingly. In the end, by traversing the map and extracting the titles, we will obtain the desired order. For the tv series the process is the same with the big exception that we have to determine the total duration of all seasons combined before we can proceed with the same algortihm.


	* CoreRecommendation - Class that contains utility functions for 							   implementing the "recommendation" command.


	The key function here is the one that implements the search recommendation. This one traverses the userlist and checks if the user has a premium subscription, if it has one we simply traverse both the movie list and series list and take out the videos that were not seen by the respective user. These are the videos we need and will return, but before that we have to also sort the list of movies accordingly. Additionally, there are also utility functions defined for checking the history of rated movies or tv series.


* Main - this is where it all comes together.

Initally, the launch functions from CoreLaunch are used to get the required lists for users, movies, tv series, actors and commands and the program starts by traversing the action list and checking each and every possible case of a command that a user can give. For most cases one or more  of the functions defined in the classes above was used to return the result, before writing it into the output JSON file.




















