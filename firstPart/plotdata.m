%% Carlo Radice 807159
%% Metodi del Calcolo Scientifico
%% A.A 2018/2019

clc;
clear;


fileID = fopen('data.txt','rt');
data = cell2mat(textscan(fileID, '%f %f %f'));
fclose(fileID);

figure(1)
semilogy(data(:, 1), data(:, 2), 'b-o');

hold on; 

semilogy(data(:, 1), data(:, 3), 'r-o');

title('Computational complexity');
xlabel('dimension');
ylabel('time');
legend('myDCT2', 'libraryDCT2');

hold off;