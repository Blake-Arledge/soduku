# implements the graph coloring algorithm

from graph import Graph

class Solve:

    def __init__(self,graph,colors):
        self.graph = graph
        self.colors = colors

    def solve(self):
        # def arcCons(cur1, cur2, connected):
        #    print "one connection so arc consistency"

        def colorCombo(colorList, x, y):
            combo = []
            if self.graph.connected(x,y):
                # then take out the doubles (r,r), (g,g), (b,b)
                for s in colorList:
                    for s2 in colorList:
                        if s != s2:
                            colorPair = (s, s2)
                            combo.append(colorPair)
            else:
                for s in colorList:
                    for s2 in colorList:
                        colorPair = (s, s2)
                        combo.append(colorPair)
            return combo

        def tryColor(cur1, cur2, neighbor, colors):
            cur1color = colors[0]
            cur2color = colors[1]
            colors2 = ["r", "g", "b"]
            neighborColor = ""

            if cur1color == cur2color:
                colors2.remove(cur1color)
            if self.graph.connected(cur1, neighbor):
                if cur1color in colors2:
                    colors2.remove(cur1color)
            if self.graph.connected(cur2, neighbor):
                if cur2color in colors2:
                    colors2.remove(cur2color)

            return colors2




        assignment = []
        vPair = []
        count = self.graph.getNumNodes()
        connected = []
        colors1 = ["r","g"]
        colors2 = ["r", "g", "b"]

        # creates pairs of nodes
        for cur1 in range(0, count):
            for cur2 in range(0, count):
                if cur1 < cur2:
                    pair = (cur1, cur2)
                    vPair.append(pair)
                    colorCombo1 = colorCombo(colors2, cur1, cur2)
        print "vPair", vPair


        # creates list of nodes connected to pair
        for cur1, cur2 in vPair:
            print "cur1", cur1
            print "cur2", cur2
            # pulls out single pair
            connected = []
            for n in range(0, count):
                if self.graph.connected(cur1, n) or self.graph.connected(cur2, n):
                    if n != cur1 and n != cur2:
                        connected.append(n)
            print "connected for", cur1, cur2, ": ", connected
            print "colorCombo", colorCombo1

            for i in range(0, len(connected)):
                for j in range(0, len(colorCombo1)):
                    availColors = tryColor(cur1, cur2, connected[i], colorCombo1[j])
                    if availColors:
                        assignment.append(availColors[0])
                    else:
                        assignment = []

            print "assignment: ", assignment



        # if self.graph.valid(assignment):
        #    print "Feasible\n"
        #else:
        #    print "Infeasible\n"

            # arc consistency helper method
            
        return assignment

        
