#include"get_next_line.h"

size_t ft_strlen(const char *str)
{
	int i = 0;
	if(!str)
		return 0;
	while(str[i])
		i++;
	return i;
}

char *ft_substr(const char *str, unsigned int start, size_t len)
{
	int i = 0;
	char *strcpy;
	
	if(ft_strlen(str) < (size_t)start)
		len = 0;
	//if(len > (ft_strlen(str)- start))
	//	strcpy = (char *)malloc(sizeof(ft_strlen(str) -start +1));
	//else
		strcpy = (char *)malloc(sizeof(char) *(len + 1));
		if(!strcpy)
			return NULL;
	while(len > 0 && str[start + i])
	{
		strcpy[i] = str[start + i];
		i++;
		len--;
	}
	strcpy[i] = '\0';
	return strcpy;
}

char	*ft_strdup(const char *str)
{
	int i = 0;
	int len = 0;
	
	while(str[len])
		len++;
	char *strcpy = (char*)malloc(sizeof(char)*(len +1));
	if(!strcpy)
		return NULL;
	while(str[i])
	{
		strcpy[i] = str[i];
		i++;
	}
	strcpy[i] = '\0';
	return strcpy;
}

char *ft_strchr(const char *str, int var)
{
	const char *str2;
	size_t i = 0;
	if(!str)
		return NULL;
	while(str[i])
	{
		if(str[i] == var)
		{
			str2 = &str[i];
			return ((char *)str2);
		}
		i++;
	}
	if(var == '\0')
	{
		str2 = &str[i];
		return((char *)str2);
	}
	return 0;
}
char *ft_strjoin(char *s1, char *s2)
{
	char *str;
	size_t i = 0;
	size_t x = 0;
	int len = 0;
	if(s1 != NULL && s2 != NULL)
		len = ft_strlen(s1) + ft_strlen(s2);
	else
		return NULL;
	str = (char *)malloc(sizeof(char)*(len + 1));
	if(!str)
		return NULL;
	while(s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while(s2[x])
	{
		str[i] = s2[x];
		i++;
		x++;
	}
	str[i] = '\0';
	free(s1);
	return str;

}


static char *read_line(int fd, char *str)
{

	char *buffer;
	char *tmp;
	int ret;
	
	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if(!buffer)
		return NULL;
	ret = 1;
	while(ret > 0)
	{
		ret = read(fd, buffer, BUFFER_SIZE);
		if(ret < 0)
			return NULL;
		if(ret == 0)
			break;
		buffer[ret] = '\0';
		if(!str)
			str = ft_strdup("");
		tmp = str;
		str = ft_strjoin(tmp, buffer);
		if(ft_strchr(str, '\n') )
			break;
	}
	free(buffer);
	return str;
	
	
}


static char *cut(char *line)
{
    char *str;
    size_t i = 0;

    while (line[i] != '\n' && line[i] != '\0')
        i++;

    if (line[i] != '\n' && line[i] != '\0')
    {
        // No se encontró un carácter de nueva línea, la línea es la última línea
        free(line);
		line = NULL;
        return NULL;
    }

    // Se encontró un carácter de nueva línea, extrae la línea y ajusta line
    str = ft_substr(line, i + 1, ft_strlen(line) - (i + 1));

    if (str != NULL && *str == '\0')
    {
        free(str);
        str = NULL;
    }
	else
	{
		line[i] = '\n';
		line[i + 1] = '\0';
	
	}

    
    return str;
}



char *get_next_line(int fd)
{
	char *line;
	static char *str;
	
	if(fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(str);
		str = NULL;
		return NULL;
	} 
	line = read_line(fd, str);
	if(!line)
	{
		free(str);
		str = NULL;
		return NULL;


	}
		
	str = cut(line);
	if (line[ft_strlen(line) - 1] != '\n') {
       		 char *line_with_nl = ft_strjoin(line, "\n");
      		 return line_with_nl;
 	   }

	return line;
}

int main()
{
 
 int fd = open("prueba.txt", O_RDONLY);

    char *line;
    int line_number = 1;

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%d %s", line_number, line);
        free(line);
        line_number++;
    }

    close(fd);

    return 0; 

/* 	int fd;
	fd = open("prueba.txt", O_RDONLY);

	
		
	char *res;
	
	res = get_next_line(fd);
	printf("%s", res);
	free(res);
	
	res = get_next_line(fd);
	printf("%s", res);
	free(res);
		
	res = get_next_line(fd);
	printf("%s", res);
	free(res);
	
 	res = get_next_line(fd);
	printf("%s", res);
	free(res); 
	
 	res = get_next_line(fd);
	printf("%s", res);
	free(res);  */

/*	res = get_next_line(fd);
	printf("%s\n", res);
	free(res); 
	
*/	
 /*	res = get_next_line(fd);
	printf("%s\n", res);
	free(res); 
	
*/
 //close(fd);



}
