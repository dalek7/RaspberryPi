clc; clear; close all;
A =load ('out_20171120_155950_888903.txt');

A = A(1:250, :);

figure;
subplot(6,1,1);
plot(A(:, 1), A(:, 2));

subplot(6,1,2);
plot(A(:, 1),A(:, 3));

subplot(6,1,3);
plot(A(:, 1),A(:, 4));

subplot(6,1,4);
plot(A(:, 1),A(:, 5))

subplot(6,1,5);
plot(A(:, 1),A(:, 6))

subplot(6,1,6);
plot(A(:, 1),A(:, 7));


