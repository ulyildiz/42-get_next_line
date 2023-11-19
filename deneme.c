#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFER_SIZE 64

static size_t ft_strlen(const char *s)
{
    size_t len = 0;
    while (s && s[len] != '\0')
        len++;
    return len;
}

void *ft_calloc(size_t count, size_t size)
{
    void *ptr = malloc(count * size);
    if (!ptr)
        return NULL;
    for (size_t i = 0; i < count * size; i++)
        ((char *)ptr)[i] = 0;
    return ptr;
}

char *ft_strjoin(char const *s1, char const *s2)
{
    if (!s1 || !s2)
        return NULL;
	size_t len1 = (s1) ? ft_strlen(s1) : 0;
    size_t len2 = (s2) ? ft_strlen(s2) : 0;

    char *s3 = (char *)ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, sizeof(char));
    if (!s3)
        return NULL;

    size_t i = 0;
    while (s1[i] != '\0')
    {
        s3[i] = s1[i];
        i++;
    }

    size_t j = 0;
    while (s2[j] != '\0')
    {
        s3[i + j] = s2[j];
        j++;
    }

    return s3;
}

static char *dup_free(char *buffer, char *tmp)
{
    char *temp = ft_strjoin(buffer, tmp);
    free(buffer);
    return temp;
}

static char check_newline(char *str)
{
    if (!str) //*
        return '\0';
    while (*str != '\0')
    {
        if (*str == '\n')
            return '1';
        str++;
    }
    return '0';
}

static char *read_file(int fd, char *buffer)
{
    char *tmp = (char *)ft_calloc(BUFFER_SIZE + 1, sizeof(char));
    if (!tmp)
        return NULL;

    int flag = 1;
    while (flag > 0)
    {
        flag = read(fd, tmp, BUFFER_SIZE);
        if (flag == -1)
        {
            free(tmp);
            free(buffer);
            return NULL;
        }
        buffer = dup_free(buffer, tmp);
        if (check_newline(tmp) == '1')
            break;
    }

    free(tmp);
    return buffer;
}

static char *read_durability(char *buffer)
{
    size_t i = 0;
    while (buffer[i] != '\n' && buffer[i] != '\0')
        i++;

    char *line = (char *)ft_calloc(i + 2, sizeof(char));
    if (!line)
        return NULL;

    i = 0;
    while (buffer[i] != '\n' && buffer[i] != '\0')
    {
        line[i] = buffer[i];
        i++;
    }

    if (buffer[i] == '\n')
        line[i++] = '\n';

    line[i] = '\0';
    return line;
}

static char *static_durability(char *buffer)
{
    size_t i = 0;
    while (buffer[i] != '\n' && buffer[i] != '\0')
        i++;

    if (!buffer[i])
    {
        free(buffer);
        return NULL;
    }

    size_t len = 0;
    while (buffer[i + len] != '\0')
        len++;

    char *newbuf = (char *)ft_calloc(len + 2, sizeof(char));
    if (!newbuf)
    {
        free(buffer);
        return NULL;
    }

    i = 0;
    while (buffer[++i] != '\0') //*
        newbuf[i - 1] = buffer[i];

    newbuf[len] = '\0';
	free(buffer);
    return newbuf;
}

char *get_next_line(int fd)
{
    static char *buffer;
    if (fd < 0 || BUFFER_SIZE < 1)
        return NULL;

    buffer = read_file(fd, buffer);
    if (!buffer || *buffer == '\0')
        return NULL;

    char *line = read_durability(buffer);
    buffer = static_durability(buffer);
    return line;
}

int main()
{
    int fd = open("example.txt", O_RDONLY);
    if (fd == -1)
    {
        perror("Error opening file");
        return 1;
    }

    char *line;
    while ((line = get_next_line(fd)) != NULL)
    {
        // Do something with the line
        printf("%s\n", line);

        // Free the line after using it
        free(line);

        // Print a debug statement to check if we are still in the loop
        printf("DEBUG: Inside loop\n");
    }

    // Close the file descriptor
    close(fd);

    // Print a debug statement after the loop
    printf("DEBUG: After loop\n");

    return 0;
}

