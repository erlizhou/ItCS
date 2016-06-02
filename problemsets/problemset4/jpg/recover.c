#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    // Open the file
	FILE* file = fopen("card.raw", "r");

	if (file == NULL)
	{
	    fclose(file);
		printf("Can not open the file.\n");
		return 1;
	}

	// First four bytes of jpeg files.
	char jpeg1[4] = {0xff, 0xd8, 0xff, 0xe0};
	char jpeg2[4] = {0xff, 0xd8, 0xff, 0xe1};

	int counter = 0;
	int open = 0;
	FILE* output;

    // Read from file.
	char buffer[512];
	char jpeg[4];
	fread(buffer, 512, 1, file);

	while (fread(buffer, 512, 1, file) > 0)
	{
		// Add four bytes to the buffer
		for (int i = 0; i < 4; i++)
		    jpeg[i] = buffer[i];

		// Check whether a jpeg
		if ((memcmp(jpeg1, jpeg, 4) == 0) || (memcmp(jpeg2, jpeg, 4) == 0))
		{
			// Construct filename
			char filename[8];
			sprintf(filename, "%03d.jpg", counter);

			if (open == 0)
			{
				output = fopen(filename, "w");
				fwrite(buffer, sizeof(buffer), 1, output);
				open++;
			}

			if (open == 1)
			{
			    fclose(output);
			    output = fopen(filename, "w");
			    fwrite(buffer, sizeof(buffer), 1, output);
			    counter++;
			}
		}
		else
		{
			if (open == 1)
				fwrite(buffer, sizeof(buffer), 1, output);
		}
	}

	// Close the file
    if (output)
      fclose(output);

	fclose(file);
	return 0;
}
