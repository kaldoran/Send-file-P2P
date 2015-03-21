## Auto-évaluation projet Reseau Team a


### Organisation

 * Nicolas Reynaud
    * Parties:
    * Nombre d'heures:

 * Kevin Bascol
    * Parties:
    * Nombre d'heures:


-------------------------------------------------------------------------------------

### Bonnes pratiques


#### "Au sujet de git"
 * Committez/pushez souvent, pour ne pas avoir peur de faire des modifications.

   *Particulièrement vrai pour Nicolas Reynaud moins pour Kevin Bascol.*

 * Remplissez des messages de commit qui décrivent les changements et la raison du changement.
 
   *Nos commits décrivent en général les changements mais jamais les raisons du changements (puisque, la plupart du temps, soit il n'y en a pas vraiment soit on se l'explique de vive voix).*

 * Remplissez tous les messages dans la même langue, en anglais si possible.

   *Tous les messages ont été remplis et en anglais.*

 * Si vous travailler à plusieurs (pair-programming), mentionner dans le message du commit quelles sont les personnes qui ont travaillé sur ce commit.

   *Chacun a son compte distinct, pas de problème pour ça.*

 * Ne committez jamais les fichiers générés (utilisez un fichier.gitignore).

   *Le gitignore est bien présent et exclue tous les fichiers générés, mais aussi les fichiers de code::blocks et ceux de cmake.*

 * Idéalement, la documentation est en markdown (.md) dans un dépôt git.

   *Toutes nos documentations sont bien disponibles en markdown et dans le repository.*


####"Au sujet du code"

 * Ecrivez votre code en anglais.

   *La totalité du code (variables, fonctions, commentaires, ...) est rédigée en anglais.*

 * Indentez votre code correctement.

   *La totalité de notre code est correctement indentée à l'aide uniquement d'espaces.
   Pour vous en assurer vous pouvez utiliser la fonction : 
   		find . -type f \( -name "*.c" -o -name "*.h" \) -exec /bin/grep -P '\t' {} \;*

 * Ne mélangez pas les tabulations et les espaces (idéalement, ne pas utilisez de tabulations).
 
   *cf ci-dessus. Cependant les tabulations ont été utilisé dans le makefile et dans les fichiers généré par Code::Blocks*

 * Veillez à la propreté de votre code : pas de variables globales/statiques, noms bien choisis (packages,classes, etc), convention (e.g.,convention java), constantes pour les constantes, ...

   *Nous avons essayé de veiller à ce que les noms des variables et des fonctions soient logiques par rapport à leurs utilité.*
   
   *Nous n'avons pas de constantes globales, et la plupart des messages ou valeurs provenant de la convention sont en constantes.*

   *En ce qui concerne la convention de nommage, nous utilisons "_" pour séparrer les mots dans les variables et les objets des structures, et pour les fonctions et les types nous les séparrons en mettant la 1ere lettre de chaque mot en majuscule. La grande majorité de notre code correspond à cette convention de nommage.*


#### "Vous écrivez un logiciel, donc"

 * Testez souvent et beaucoup.

    *De nombreux tests ont été effectués pendant la programmation, que ce soit dans notre team ou avec la team b.*

 * Automatisez vos tests qui peuvent l’être.

    *Nous ne disposons d'aucun test automatique.*

 * Documenter comment utiliser, compiler, tester et lancer votre projet.

    *Toutes les informations sur l'utilisation de notre projet sont disponibles dans "README.md" et "Windows Compatibility.md".*

 * Documenter comment comprendre et reprendre votre projet.

    *Toutes ces informations sont disponibles dans les documents précédents et dans "Convention.md".*


















