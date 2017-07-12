# Webapp Creator library

## manifestEdit

### Parametros requeridos:

  - **name**. Nombre del paquete. Siempre en minúsculas y excluyendo “com.ubuntu.” al inicio del propio nombre.

  - **desc**. Descripción de la webapp en cuestión.

  - **title**. Título o nombre de la webapp. Aparecerá en tienda y en la scope de Apps.

  - **version**. Versión de desarrollo de la webapp.

  - **maint**. Desarrollador o mantenedor de la webapp.

### Efecto actual:

Edita “/tmp/webappCreator/manifest.json”, introduciendo todas los parametros anteriormente mencionados en sus respectivos campos.

_**NO crea el fichero** “manifest.json”. Se ha de crear una conexión con la linea de comandos para **crear tanto el directorio** webappCreator, **como el archivo** “manifest.json”. Preferiblemente bajo el código front-end **en qml**._



## apparmorEdit

### Parametros requeridos:

  - **groups**. Vector de activación para los permisos. Su activación se valida igualando su componente de vector correspondiente a 1 (Ej. groups[9]=1 activa los permisos de historial). Se organizan alfabéticamente:

    - groups[0]. accounts
    - groups[1]. audio
    - groups[2]. calendar
    - groups[3]. camera
    - groups[4]. connectivity
    - groups[5]. contacts
    - groups[6]. content_exchange
    - groups[7]. content_exchange_source
    - groups[8]. debug
    - groups[9]. history
    - groups[10]. in-app-purchases
    - groups[11]. keep-display-on
    - groups[12]. location
    - groups[13]. microphone
    - groups[14]. music_files
    - groups[15]. music_files_read
    - groups[16]. networking
    - groups[17]. picture_files
    - groups[18]. picture_files_read
    - groups[19]. push_notification_client
    - groups[20]. sensors
    - groups[21]. usermetrics
    - groups[22]. video
    - groups[23]. video_files
    - groups[24]. video_files_read
    - groups[25]. webview

  - **name**. Nombre del paquete. Siempre en minúsculas y excluyendo “com.ubuntu.” al inicio del propio nombre.

### Efecto actual:

Edita “/tmp/webappCreator/**name**.apparmor”, introduciendo todas los parametros anteriormente mencionados en sus respectivos campos.

_**NO crea el fichero** “**name**.apparmor”. Se ha de crear una conexión con la linea de comandos para **crear tanto el directorio** webappCreator, **como el archivo** “**name**.apparmor”. Preferiblemente bajo el código front-end **en qml**._



## desktopEdit

### Parametros requeridos:

  - **name**. Nombre del paquete. Siempre en minúsculas y excluyendo “com.ubuntu.” al inicio del propio nombre.

  - **com**. Comentario acerca de la webapp. Espacio para un eslogan o una muy breve descripción.

  - **title**. Título o nombre de la webapp. Aparecerá en tienda y en la scope de Apps.

  - **url**. URL de la web a capturar en la webapp. Solo debe contener el dominio (y subdominios si es el caso) de la web. NO se ha de escribir “http://” o “https://”.

  - **arg**. Vector de activación para los argumentos. Su activación se valida igualando su componente de vector correspondiente a 1 (Ej. arg[0]=1 activa el argumento `--fullscreen`). Siguen este orden:

    - arg[0]. `--fullscreen`
    - arg[1]. `--accountProvider=PROVIDER`
    - arg[2]. `--accountSwitcher`
    - arg[3]. `--store-session-cookies`
    - arg[4]. `--enable-media-hub-audio`
    - arg[5]. `--user-agent-string=USER_AGENT`
    - arg[6]. `--enable-back-foward`
    - arg[7]. `--enable-addressbar`

  Nótese que `--enable-back-foward` incluye `--enable-addressbar`.

  - **subUrl1, subUrl2 y subUrl3**. Son otras URLs a las que puede acceder a la webapp. Deben de ser ajenas al dominio de la URL principal.

  - **urls**. Vector de activación para las subURLs. Su activación se valida igualando su componente de vector correspondiente a 1 (Ej. Urls[1] activa subUrl2). Siguen este orgen:

    - urls[0]. subUrl1
    - urls[1]. subUrl2
    - urls[2]. subUrl3

  - **PROVIDER**. Proveedor para el manejo de cuentas de Ubuntu ONE. Especificado por el usuario si desea utilizar el argumento --accountProvider.

  - **USER_AGENT**. Necesario si se quiere especificar un User-Agent alternativo al predeterminado. Debe ser especificado por el usuario si desea utilizar el argumento --user-agent-string.

  - **https**. Booleano que en caso afirmativo, escribirá “https://” en lugar de “http://” en todas las URLs especificadas.

  - **ogra**. Booleano que en caso afirmativo escribirá un archivo “**name**.desktop” de Ogra Container. En caso negativo, procederá a escribir el archivo “**name**.desktop” de una webapp típica.

### Efecto actual:

Edita “/tmp/webappCreator/**name**.desktop”, introduciendo todas los parametros anteriormente mencionados en sus respectivos campos.

_**NO crea el fichero** “**name**.desktop”. Se ha de crear una conexión con la linea de comandos para **crear tanto el directorio** webappCreator, **como el archivo** “**name**.desktop”. Preferiblemente bajo el código front-end **en qml**._



## configEdit

### Parametros requeridos:

  - **name**. Nombre del paquete. Siempre en minúsculas y excluyendo “com.ubuntu.” al inicio del propio nombre.

  - **maint**. Desarrollador o mantenedor de la webapp.

  - **url**. URL de la web a capturar en la webapp. Solo debe contener el dominio (y subdominios si es el caso) de la web. NO se ha de escribir “http://” o “https://”.

  - **subUrl1, subUrl2 y subUrl3**. Son otras URLs a las que puede acceder a la webapp. Deben de ser ajenas al dominio de la URL principal.

 - **urls**. Vector de activación para las subURLs. Su activación se valida igualando su componente de vector correspondiente a 1 (Ej. Urls[1] activa subUrl2). Siguen este orgen:

    - urls[0]. subUrl1
    - urls[1]. subUrl2
    - urls[2]. subUrl3

  - **hapticLinks**. Booleano que en caso afirmativo habilita los enclaces “hápticos” o “táctiles”.

  - **USER_AGENT**. Necesario si se quiere especificar un User-Agent alternativo al predeterminado. Debe ser especificado por el usuario.

  - **https**. Booleano que en caso afirmativo, escribirá “https://” en lugar de “http://” en todas las URLs especificadas.

  - **UA**. Booleano, que en caso afirmativo, habilita la inclusión de un **USER_AGENT** personalizado.

  - **audibleLinks**. Booleano que en caso afirmativo habilita sonidos en los enclaces.

### Efecto actual:

Edita “/tmp/webappCreator/config.js”, introduciendo todas los parametros anteriormente mencionados en sus respectivos campos.

_**NO crea el fichero** “config.js”. Se ha de crear una conexión con la linea de comandos para **crear tanto el directorio** webappCreator, **como el archivo** “config.js”. Preferiblemente bajo el código front-end **en qml**._



## qmlEdit

### Parametros requeridos:

  - **name**. Nombre del paquete. Siempre en minúsculas y excluyendo “com.ubuntu.” al inicio del propio nombre.

  - **maint**. Desarrollador o mantenedor de la webapp.

### Efecto actual:

Edita todos los ficheros contenidos en el directorio “/tmp/webappCreator/qml”. Todos los parametros anteriormente mencionados se incluyen tan solo en el archivo “Main.qml”. El resto de archivos no necesita nunguna edición especial de momento.

_**NO crea NINGUNO de los anteriores ficheros**. Se ha de crear una conexión con la linea de comandos para **crear tanto los directorios necesarios** webappCreator, **como los archivos correspondientes**. Todo ello, preferiblemente bajo el código front-end **en qml**._
