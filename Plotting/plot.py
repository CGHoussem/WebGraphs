import tkinter as tk
from tkinter import filedialog
import matplotlib.pyplot as plt
import csv


def get_plotsdata(dirname):
    plotsdata = [
        {'title': 'Facebook Graph', 'filename': f'{dirname}/PlottingFacebook.csv', 'output': 'output/facebook.png'},
        {'title': 'GitHub Graph', 'filename': f'{dirname}/PlottingGitHub.csv', 'output': 'output/github.png'},
        {'title': 'Road Network Graph', 'filename': f'{dirname}/PlottingRoadNetwork.csv', 'output': 'output/road_network.png'},
        {'title': 'Twitch Graph', 'filename': f'{dirname}/PlottingTwitch.csv', 'output': 'output/twitch.png'},
        {'title': 'Wikipedia 1 Graph', 'filename': f'{dirname}/PlottingWikipedia1.csv', 'output': 'output/wikipedia1.png'},
        {'title': 'Wikipedia 2 Graph', 'filename': f'{dirname}/PlottingWikipedia2.csv', 'output': 'output/wikipedia2.png'}
    ]
    return plotsdata

def save_plot(title, csv_filename, output_filename):
    x_data = []
    y_data = []

    with open(csv_filename) as csvfile:
        reader = csv.DictReader(csvfile, delimiter=';')
        for row in reader:
            x_data.append(int(row['Degree'])) 
            y_data.append(int(row['Occurrence']))

    plt.scatter(x_data, y_data)
    
    plt.title(title)
    plt.xlabel('Degrés')
    plt.ylabel('Fréquence d\'apparition')
    plt.grid(True)
    
    plt.savefig(output_filename)
    plt.cla()


if __name__ == "__main__":
    root = tk.Tk()
    root.withdraw()

    dir_path = filedialog.askdirectory()

    print('Creating plots...')
    for plotdata in get_plotsdata(dir_path):
        title = plotdata['title']
        filename = plotdata['filename']
        output = plotdata['output']

        save_plot(title, filename, output)

    print('All plots has been successfully created.')