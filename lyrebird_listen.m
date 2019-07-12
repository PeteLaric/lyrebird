% lyrebird_listen.m
% A MATLAB/Octave script to convert audio of a Lyrebird song to data using
% machine learning (ML) techniques.  lyrebird_listen loads the learned
% parameters that were generated by lyrebird_learn, and uses the
% pre-trained ML model to accomplish the actual transcription of audio to
% data.
% (cc) BY 2019 Pete Laric
% http://www.PeteLaric.com

clear all
clc

Theta = csvread('lyrebird_listen_Theta.csv');

input_filename = 'lyrebird_song.wav'
%input_filename = 'lyrebird_song.ogg' %also works perfectly!!  :D

%audiowrite(output_filename, audio_buffer, sample_rate);
[audio_buffer, sample_rate] = audioread(input_filename);

% get some useful data
sample_rate
seconds_per_blip = 0.20
samples_per_blip = round(sample_rate * seconds_per_blip)
audio_buffer_length = length(audio_buffer)
encoded_bytes = audio_buffer_length / samples_per_blip

% create X matrix
X = zeros(encoded_bytes, samples_per_blip);
for i=1:encoded_bytes
    
    start_index = samples_per_blip * (i - 1) + 1
    end_index = start_index + samples_per_blip - 1
    X(i,:) = audio_buffer(start_index:end_index);
    
end

[m, n] = size(X);
X = [ones(m,1) X]; %add bias unit column
[m, n] = size(X)

Y = csvread('exhaustive_bytes.txt');

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

H_bin = H >= 0.5;

% convert H (matrix of ones and zeros, decoded from audio) into binary data
% using linear algebra.  :D
coefs = [128; 64; 32; 16; 8; 4; 2; 1];
data = H_bin * coefs;

temp_filename = 'temp.dat'
outfile = fopen(temp_filename, 'wb');
fprintf(outfile, '%s', data);
fclose(outfile);

get_filename_and_copy(temp_filename);

disp('Audio decomposed successfully.');
