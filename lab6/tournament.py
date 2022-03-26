# Simulate a sports tournament

import csv
import sys
import random

# Number of simluations to run
N = 1000


def main():

    # Ensure correct usage
    if len(sys.argv) != 2:
        sys.exit("Usage: python tournament.py FILENAME")

    # This will become a list of dictionaries
    teams = []
    # "with" will open the file and close it when it reaches the end
    with open(sys.argv[1], "r") as file:
        # "csv.DictReader" will prime the file in dictionary format
        # using the first row in the csv as the keys, e.g. "team" and "rating"
        reader = csv.DictReader(file)
        # Iterate through the reader dictionary object into the new
        # team dictionary 1 row at a time
        for team in reader:

            # teams[] will look like this
            #   teams[
                    # {
                    # "team": "team name", e.g. string England
                    # "rating": "team rating" e.g. integer 1098
                    # }
                    # {
                    # "team": "team name",
                    # "rating": "team rating"
                    # }
                    #]

            # Convert the "team["rating"]" string into an integer
            team["rating"] = int(team["rating"])
            # Add the current "team" dictionary to the "teams" list
            # Repeat the process until the end of the file
            teams.append(team)

    # Create a dictionary which will hold how many victories a team has
    # The team name being the key and the number of victories being the
    # value
    counts = {}
    # counts {} will look as follows
    #    counts{
              # "team name": "wins",
              # "team name": "wins",
              # "team name": "wins"
              # }

    for x in range(N):
        # winner string will be the winner of a simulated tournament
        winner = simulate_tournament(teams)
        # If the winner already exists in the "counts" dictionary then add 1 to victory count
        if winner in counts:
            counts[winner] += 1
        # If the winner does not exist in the "counts" dictionary then add the winner to the dictionary
        # with a value of 1
        else:
            counts[winner] = 1

    # Print each team's chances of winning, according to simulation
    for team in sorted(counts, key=lambda team: counts[team], reverse=True):
        print(f"{team}: {counts[team] * 100 / N:.1f}% chance of winning")


def simulate_game(team1, team2):
    """Simulate a game. Return True if team1 wins, False otherwise."""
    rating1 = team1["rating"]
    rating2 = team2["rating"]
    # An equation to calculate the probability of a team beating the other
    probability = 1 / (1 + 10 ** ((rating2 - rating1) / 600))
    # ".random()" generates a random float between 0 and 1
    return random.random() < probability


def simulate_round(teams):
    """Simulate a round. Return a list of winning teams."""
    # Create a local list to hold the winners of a round of matches
    winners = []

    # Simulate games for all pairs of teams
    # starting with teams[0] and teams[1] then
    # teams[2] and teams[3] and so on

    # This for loop runs until a round is finished
    # E.g. First round: 16 teams, 8 matches, 8 winners
    # Second round: 8 teams, 4 matches, 4 winners
    # Third round: 4 teams, 2 matches, 2 winners
    # Fourth round: 2 teams, 1 match, 1 winner
    for i in range(0, len(teams), 2):
        # if simulate_game returns True then team [i] wins
        if simulate_game(teams[i], teams[i + 1]):
            winners.append(teams[i])
        # else team[i + 1] wins
        else:
            winners.append(teams[i + 1])

    # There will always be 1 winner after a simulation
    return winners


def simulate_tournament(teams):
    """Simulate a tournament. Return name of winning team."""
    # As long as there is more than 1 team in the list of teams
    # then simulate a round until 1 remains
    while len(teams) > 1:
        # "teams" will get smaller by a factor of 2 each time "simulate_rounds" is run
        # When "simulate_rounds" is called it sends "teams" as it currently will be then
        # it returns the "winners" list of dictionaries and updates "teams" appropriately
        teams = simulate_round(teams)
    # "teams[0]" will be the only team left in the list of dictionaries after the simulation has run
    return teams[0]["team"]


if __name__ == "__main__":
    main()
