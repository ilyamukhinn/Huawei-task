import pandas as pd
import os
import sys
import matplotlib.pyplot as plt

def plot_init():
    plt.xlabel('Experiment number')
    box = plt.subplot().get_position()
    plt.subplot().set_position([box.x0, box.y0, box.width * 0.8, box.height])

experiments_per_mode = int(sys.argv[1])

def print_one_mode(mode, one_cycle_time, two_cycle_time):
    plt.clf()
    plt.title(mode)
    plt.gcf().set_size_inches(18.5, 10.5)
    plt.plot(list(range(1,experiments_per_mode + 1)), one_cycle_time, label='One cycle time')
    plt.plot(list(range(1,experiments_per_mode + 1)), two_cycle_time, label='Two cycles time', linestyle='--')
    plt.legend(loc='center left', bbox_to_anchor=(1, 0.5))
    plt.savefig(mode + ".png")

def print_all_modes(modes, one_cycle_values, two_cycles_values):
    plt.clf()
    plt.title("Comparison of modes")
    plt.gcf().set_size_inches(29.5, 10.5)

    for i in range(len(modes)):
        plt.plot(list(range(1,experiments_per_mode + 1)), one_cycle_values[i], label='One cycle time(\n{mode})'.format(mode=modes[i]))
        plt.plot(list(range(1,experiments_per_mode + 1)), two_cycles_values[i], label='Two cycles time(\n{mode})'.format(mode=modes[i]))
    
    plt.legend(loc='center left', bbox_to_anchor=(1, 0.5))
    plt.savefig("Comparison of modes.png", dpi=199)

def print_avg_all_modes(modes, one_cycle_avg_values, two_cycles_avg_values):
    plt.clf()
    plt.title("Comparison of modes")
    plt.gcf().set_size_inches(18.5, 10.5)
    for i in range(len(modes)):
        plt.scatter(i + 1, one_cycle_avg_values[i], label='One cycle time(\n{mode})'.format(mode=modes[i]))
        plt.scatter(i + 1, two_cycles_avg_values[i], label='Two cycles time(\n{mode})'.format(mode=modes[i]))
    plt.legend(loc='center left', bbox_to_anchor=(1, 0.5))
    plt.savefig("Comparison of modes (avg).png")

def main():
    data = pd.read_csv(os.path.dirname(os.path.realpath(__file__)) + os.path.sep + "data.csv")

    headers = data.head(0).columns.to_list()
    modes = data[headers[0]].iloc[0::experiments_per_mode + 1].to_list()

    one_cycle_values = list() 
    for i in range(len(modes)):
        one_cycle_values.append(data[data[headers[1]].notna()][headers[1]].iloc[i * experiments_per_mode:i * experiments_per_mode + experiments_per_mode:1].to_list())
    
    two_cycles_values = list() 
    for i in range(len(modes)):
        two_cycles_values.append(data[data[headers[2]].notna()][headers[2]].iloc[i * experiments_per_mode:i * experiments_per_mode + experiments_per_mode:1].to_list())

    plot_init()

    for i in range(len(modes)):
        print_one_mode(modes[i], one_cycle_values[i], two_cycles_values[i])
    
    print_all_modes(modes, one_cycle_values, two_cycles_values)

    one_cycle_avg_values = list()
    two_cycles_avg_values = list()
    for i in range(len(modes)):
        one_cycle_avg_values.append(sum(one_cycle_values[i]) / len(one_cycle_values[i])) #AVG
        two_cycles_avg_values.append(sum(two_cycles_values[i]) / len(two_cycles_values[i])) #AVG

    print_avg_all_modes(modes, one_cycle_avg_values, two_cycles_avg_values)

if __name__ == "__main__":
    main()