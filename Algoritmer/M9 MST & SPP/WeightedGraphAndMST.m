% Vertices
vertices = {'A', 'B', 'F', 'D', 'C', 'E'};

% Edges and their weights
edges = [1, 2, 2; 
         1, 3, 1; 
         2, 4, 3; 
         2, 5, 4; 
         4, 2, 1; 
         4, 6, 8; 
         6, 3, 1; 
         6, 5, 1; 
         5, 3, 2; 
         5, 1, 7; 
         5, 4, 7];

% Create a graph
G = graph(edges(:, 1), edges(:, 2), edges(:, 3), vertices);

% Construct a minimum spanning tree
MST = minspantree(G);

% Plot the original graph
figure;
h = plot(G, 'EdgeLabel', G.Edges.Weight, 'Layout', 'force', 'EdgeColor', 'k', 'NodeColor', 'b', 'NodeLabel', G.Nodes.Name);
title('Original Graph');

% Plot the minimum spanning tree
figure;
h_MST = plot(MST, 'EdgeLabel', MST.Edges.Weight, 'Layout', 'force', 'EdgeColor', 'k', 'NodeColor', 'b', 'NodeLabel', MST.Nodes.Name);
title('Minimum Spanning Tree');
