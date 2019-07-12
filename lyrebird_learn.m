% lyrebird_learn.m
% A MATLAB/Octave script to convert audio of a Lyrebird song to data using
% machine learning techniques.  lyrebird_learn learns how to accomplish the
% transcription by running multi-output, multivariate regression on an
% example data set.  The learned parameters are then saved to a file
% (lyrebird_listen_Theta.csv), which is used by lyrebird_listen to do the
% actual transcription task.
% (cc) BY 2019 Pete Laric
% http://www.PeteLaric.com

clear all
clc

input_filename = 'exhaustive_bytes.wav'

%audiowrite(output_filename, audio_buffer, sample_rate);
[audio_buffer, sample_rate] = audioread(input_filename);

% get some useful data
sample_rate
seconds_per_blip = 0.20
samples_per_blip = round(sample_rate * seconds_per_blip)
audio_buffer_length = length(audio_buffer)
encoded_bytes = audio_buffer_length / samples_per_blip

% crop off embedded filename
bytes_to_retain = 256
samples_to_retain = bytes_to_retain * samples_per_blip
audio_buffer = audio_buffer(end-samples_to_retain+1:end);
disp('audio buffer cropped.');
size(audio_buffer)

% create X matrix
X = zeros(bytes_to_retain, samples_per_blip);
for i=1:bytes_to_retain
    
    start_index = samples_per_blip * (i - 1) + 1
    end_index = start_index + samples_per_blip - 1
    X(i,:) = audio_buffer(start_index:end_index);
    
end

[m, n] = size(X);
X = [ones(m,1) X]; %add bias unit column
[m, n] = size(X)

Y = csvread('exhaustive_bytes.txt');

% regress
fprintf('performaing regression analysis...\n\n');
Theta = zeros(n, 8);
for i=1:8
    
    % regress for ith column of Y matrix
    y = Y(:,i);
    
    theta = pinv(X' * X) * X' * y;
    
    h = X * theta;
    h_bin = h >= 0.5;
    correct = h_bin == y;
    accuracy = mean(correct)
    
    Theta(:,i) = theta;
    
end

disp('done.');

% convert Y (matrix of ones and zeros) into 256 integers, 0:255
coefs = [128; 64; 32; 16; 8; 4; 2; 1]
y_binary = Y * coefs

% generate 'hypotheses' for each output bit
h1 = X * Theta(:,1);
h2 = X * Theta(:,2);
h3 = X * Theta(:,3);
h4 = X * Theta(:,4);
h5 = X * Theta(:,5);
h6 = X * Theta(:,6);
h7 = X * Theta(:,7);
h8 = X * Theta(:,8);

% all hypotheses, in matrix form
H = [h1 h2 h3 h4 h5 h6 h7 h8];

fprintf('writing Theta to file...');
csvwrite('lyrebird_listen_Theta.csv', Theta);
fprintf('done.\n\n');

save('lyrebird_learn.mat');
