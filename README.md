<h1>CS50 - Exercises and Problem Sets</h1>
<h2>This repository contains exercises and problem sets from the CS50 course at Harvard University. Below are the details and purpose of each directory up to Week 9.</h2>
<ul>
    <li>
    <ul>
    <h3>Week 0 (Scratch)</h3>
        <li><strong>Scratch:</strong> A soccer game video created using Scratch.</li>
    </ul>
    </li>
    <li><ul>
    <h3>Week 1 (C)</h3>
    <li><strong>Hello, Me:</strong> A simple program that prints 'Hello, Me!' to the console, where 'Me' is an input provided by the user.</li>
    <li><strong>Mario (More):</strong> A program that prints a pyramid shape in the console similar to the one in the Mario game.</li>
    <li><strong>Credit:</strong> A program that takes a credit card number and checks if it is valid using the Luhn’s Algorithm. If valid, it returns the type of card (AMEX, VISA, MASTERCARD); otherwise, it returns (INVALID).</li>
    </ul></li>
    <li>
    <ul>
    <h3>Week 2 (Array)</h3>
    <li><strong>Scrabble:</strong> A game where the program takes two inputs (Player 1's and Player 2's words) and determines the winner based on the sum of the point values for each letter in the current player’s word. If there is a winner, it returns the winner; otherwise, it returns Tie.</li>
    <li><strong>Readability:</strong> A program that uses the Coleman-Liau index to determine the (U.S.) grade level required to understand a given text.</li>
    <li><strong>Substitution:</strong> A substitution cipher program that encrypts a message by replacing each letter with another letter. If the key is not valid or the encryption alphabet does not have 26 non-repeating letters, it returns an error message. Otherwise, it returns the encrypted message.</li>
    </ul></li>
    <li><ul>
    <h3>Week 3 (Algorithms)</h3>
    <li><strong>Sort:</strong> A program that includes three sorting models (sort1, sort2, and sort3) and requires determining which sorting model each file uses (Bubble, Selection, Merge) by using the "time" command on different data types (sorted, random, descending).</li>
    <li><strong>Plurality:</strong> A program that processes candidates from an election and the quantity of votes each receives. Each voter selects one candidate, and the program returns the winner of the election.</li>
    <li><strong>Tideman:</strong> A program that processes candidates from an election and the quantity of votes each receives, with voters ranking the candidates in order of preference. The program determines the winner of the election based on these rankings.</li>
    </ul></li>
    <li><ul>
    <h3>Week 4 (Memory)</h3>
    <li><strong>Volume:</strong> A program that takes a WAV file and a scaling factor to adjust the audio’s volume. It reads the file, processes each sample by multiplying it by the factor, and writes the result to a new WAV file.</li>
    </ul></li>
    <li><strong>Filter:</strong> A program that applies image filters to BMP files by manipulating the pixel values in a bitmap. The goal is to implement edge detection to highlight boundaries in images. This involves processing 24-bit BMP files where each pixel is represented by three color components (blue, green, red). The program reads the image data, applies the filter, and writes the modified image back to a new BMP file.</li>
    </ul></li>
    <li><ul>
    <h3>Week 5 (Data Structures - C)</h3>
    <li><strong>Inheritance:</strong> A program that simulates the inheritance of blood types in a family. It determines a child’s possible blood types based on the blood types of the parents. Each parent contributes one allele to their child, and the program calculates all possible combinations of blood types for the child based on the parents' alleles.</li>
    <li><strong>Speller:</strong> A program that spell-checks a file using a hash table. It involves implementing functions to load a dictionary into memory, check if words from a file are in the dictionary, and manage memory efficiently. The goal is to optimize the hash table for quick lookups and ensure accurate spell-checking.</li>
    </ul></li>
    <li><ul>
    <h3>Week 6 (Python)</h3>
    <li><strong>sentimental-hello:</strong> The same program from Week 1 (Hello, Me), but now implemented in Python.</li>
    <li><strong>sentimental-mario-more:</strong> The same program from Week 1 (Mario), but now implemented in Python.</li>
    <li><strong>sentimental-redit:</strong> The same program from Week 1 (Credit), but now implemented in Python.</li>
    <li><strong>sentimental-readability:</strong> The same program from Week 2 (Readability), but now implemented in Python.</li>
    </ul></li>
    <li><ul>
    <h3>Week 7 (SQL)</h3>
    <li><strong>Songs:</strong> Write SQL queries to analyze a database of the 100 most-streamed songs on Spotify in 2018. The project involves querying a SQLite database to answer questions about song and artist data, including attributes like danceability, energy, and tempo.</li>
    <li><strong>Movies:</strong> Write SQL queries to analyze a SQLite database of IMDb movie data. The project involves creating queries to retrieve information such as movie titles, release years, ratings, and actor/director details based on specific criteria. Queries include tasks like listing movies from specific years, finding average ratings, and identifying movies with particular actors or directors.</li>
    <li><strong>Fiftyville:</strong> Solve the mystery of the stolen duck in Fiftyville by querying a SQLite database. The task involves identifying the thief, their escape city, and their accomplice using SQL queries on the provided data. Document the SQL queries and thought process in a log file to detail how you arrived at the solution.</li>
    </ul></li>
    <li><ul>
    <h3>Week 8 (HTML, CSS, JavaScript)</h3>
    <li><strong>Trivia Quiz:</strong> A web page with multiple-choice and free response trivia questions. HTML is used for structure, CSS for styling, and JavaScript for interactivity, including color changes and feedback based on user answers.</li>
    <li><strong>Homepage:</strong> A simple web page to introduce yourself and showcase your interests, hobbies, or other personal information. The project involves using HTML to structure the content, CSS to style the page, and JavaScript to add interactivity.</li>
    </ul></li>
    <li><ul>
    <h3>Week 9 (Flask)</h3>
    <li><strong>Birthdays:</strong> A Flask web application to manage friend's birthdays. It allows users to view and add birthdays to a SQLite database. The app features a form for submitting new birthdays and displays a list of existing ones. It handles both GET requests to show the list and POST requests to add new entries to the database.</li>
    <li><strong>Finance:</strong> A web application that allows users to manage their finances. It involves creating a front-end and back-end for the application, using Flask for the server-side logic and a database to store user information and transactions.</li>
    </ul></li>
</ul>
