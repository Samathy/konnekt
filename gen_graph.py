import json

from random import randint
from string import ascii_lowercase


def main():
    g_dict = {}

    labels = []
    edges = 0

    with open("graph.json", "w") as g:
        g_dict["vertices"] = []
        for i in range(0, len(ascii_lowercase)):
                label = ascii_lowercase[i]
                g_dict["vertices"].append({"label":label})
                labels.append(label)

        g_dict["edges"] = []
        for i in range(0, round(len(labels)/3)):
            l1 = labels[randint(0, len(labels)-1)]
            l2 = labels[randint(0, len(labels)-1)]

            edges += 1

            g_dict["edges"].append({"v1":l1, "v2":l2})


        g.write(json.dumps(g_dict, indent=4))

        print("Verticies: %s" %( len(labels)))
        print("Edges: %s" %(edges))



if __name__ == "__main__":
    main()
