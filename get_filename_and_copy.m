function [ output_args ] = get_filename_and_copy( temp_filename )
%GET_FILENAME_AND_COPY Strips filename out of recently-decomposed file,
%then uses it to make a copy of the temporary file.
%   This function modularizes the process of restoring the filename of
%   whatever file was used to generate the Lyrebird song to begin with.
%   This function is similar to the C function "get_filename_and_copy()"
%   from "lyrebird_decompose.c".

infile = fopen(temp_filename, 'rb');

% extract filename from temporary file
output_filename = fgetl(infile)

% create file with output filename; open for binary write
outfile = fopen(output_filename, 'wb');

fprintf('copying %s to %s...', temp_filename, output_filename);

% copy file contents
s = fread(infile);
fwrite(outfile, s);

% close files
fclose(infile);
fclose(outfile);

fprintf('done!\n\n');

end

