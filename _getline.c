






























































/*free(buffer);*/
				/*(*lineptr)[c] = EOF;*/
				/*return (c);*/
				break;
			}
			/*printf("beginning for\n");//debug check*/
			if (buffer[begin] == '\n')
			{
				(*lineptr)[c] = '\n';
				begin++;
				c++;
				(*lineptr)[c] = '\0';
				return (c);
			}
			else
			{
				(*lineptr)[c] = buffer[begin];
			}
			c++;
		}
		if (c + begin >= 1024)
		{
			old_size = size;
			size = size + 1024;
			*lineptr = _realloc(*lineptr, old_size, size);
			if (*lineptr == NULL)
			{
				return (-1);
			}
		}
		else
		{
			(*lineptr)[old_size + begin] = 0;
			return (c);
		}
		/*printf("j: %d, i:%d, r:%d\n", j, i ,r);*/
	}
}
