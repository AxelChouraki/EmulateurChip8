# Définition du compilateur à utiliser
CC = g++

# Options de compilation
CFLAGS = -Wall -Wextra -g -I"C:/msys64/mingw64/include"
# -Wall : Active les avertissements de base du compilateur
# -Wextra : Active les avertissements supplémentaires
# -g : Ajoute des informations de débogage pour faciliter le débogage
# -I"C:/msys64/mingw64/include" : Spécifie où se trouvent les fichiers d'en-tête (headers) de la SDL2

# Options de l'éditeur de liens (Linker)
LDFLAGS = -L"C:/msys64/mingw64/lib" -lSDL2
# -L"C:/msys64/mingw64/lib" : Indique au linker où trouver les bibliothèques
# -lSDL2 : Lie le programme avec la bibliothèque SDL2 (nécessaire pour utiliser SDL2)

# Définition du nom de l'exécutable généré
TARGET = emulation_chip8.exe

# Liste des fichiers source (.c) que nous allons compiler
SRCS = main.c cpu.c pixel.c

# Liste des fichiers objets générés à partir des sources (.c → .o)
# On remplace l'extension .c par .o pour chaque fichier source
OBJS = $(SRCS:.c=.o)

# Règle principale : compilation de l'exécutable
# Cette règle va compiler les fichiers objets (.o) et les lier pour créer l'exécutable
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)
	# $(CC) : Le compilateur
	# $(OBJS) : Les fichiers objets à lier
	# -o $(TARGET) : Spécifie le nom de l'exécutable généré
	# $(LDFLAGS) : Les options de l'éditeur de liens (liaison avec SDL2)

# Règle pour compiler chaque fichier source en fichier objet
# %.o : Le fichier objet cible (remplaçant .o)
# %.c : Le fichier source cible (remplaçant .c)
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
	# $(CC) : Le compilateur
	# $(CFLAGS) : Les options de compilation (avertissements, débogage, etc.)
	# -c : Signifie que le fichier source doit être compilé mais pas lié
	# $< : Le fichier source (.c)
	# -o $@ : Le fichier objet généré (.o)

# Nettoyage des fichiers générés
# Cette règle supprime les fichiers objets et l'exécutable
clean:
	rm -f $(OBJS) $(TARGET)
	# rm -f : Force la suppression des fichiers sans erreur si un fichier est absent
	# $(OBJS) : Les fichiers objets générés
	# $(TARGET) : L'exécutable généré
