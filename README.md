Fibonacciho halda

Jedna se o priority queue, tedy datovou strukturu, ktera z vlozenych dat vzdy vytahuje takova, ktera maji nejmensi klic podle daneho klicoveho systemu.


fib::Fib_Heap<T>(T null_data) halda;   	// konstruktor haldy; T je typ dat, ktera budou v halde ulozena; T null_data je hodnota, kterou halda vrati v pripade chyby, napriklad pri pokusu o zjisteni minimalni hodnoty v prazdne halde

void halda.insert(T data, int key);	// tvori novy prvek s dvojici data-klic a vklada ho do haldy

bool halda.empty();			// vraci true, pokud je halda prazdna, jinak vraci false

T halda.minimum();			// vraci hodnotu prvku v halde s nejmensim klicem

T halda.extract_min();			// stejne jako minimum(), navic tento prvek odstrani