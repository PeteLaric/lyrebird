function [ Score ] = load_lyrebird_song( input_filename )
%LOAD_LYREBIRD_SONG Loads a song in .lyrebird format.
%   Converts notes to numbers and returns a numeric matrix.

infile = fopen(input_filename)

while (~feof(infile))

    str = fgetl(infile);
    
    char_vector = sscanf(str, '%s');
    
    num_vector = notes_to_numbers(char_vector)
    
    if (exist('Score'))
        
        Score = [Score; num_vector];
        
    else
        
        Score = num_vector;
        
    end
    
end

fclose(infile)

end

