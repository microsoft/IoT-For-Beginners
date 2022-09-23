# Limpia tu proyecto

Después de completar, se recomienda eliminar tus recursos en línea.

Durante las lecciones de cada proyecto, puede que hayas creado algunos de los siguientes:

* Grupo de recursos (Resource Group)
* Hub de internet de las cosas (IoT hub)
* Registro de dispositivos IoT
* Cuenta de almacenamiento
* Aplicación de funciones
* Cuenta de mapas de Azure
* Proyecto personalizado de visión
* Contenedor de registros de Azure
* Recursos de sercivios cognitivos

La mayor parte de estos servicios no tienen costo, bien sea porque son totalmente gratuitos o porque estás usando la versión gratuita. Para los servicios que requieren una versión paga, puede que hayas estado usándolos entre el rango en el que no se efectúa ningún cobro o sólo costará unos cuantos centavos.

Inclusive con el bajo costo de los recursos, vale la pena eliminiarlos cuando hayas acabado ya que sólo puedes mantener un Hub de IoT habilitado con la versión gratuita así que si, por ejemplo, quisieras crear uno nuevo, necesitarías usar una versión paga de los sistemas.

Todos los servicios fueron creados dentro de grupos de recursos (Resource Group) y esto hace que sea más fácil administrarlos. Puedes eliminiar el grupo de recursos y todos los servicios en ese grupo serán eliminados con él.

Para eliminar un grupo de recursos, ejecuta el siguiente comando en tu terminal o consola de comandos de Azure:

```sh
az group delete --name <nombre-grupo-de-recursos>
```

Reemplazando `<nombre-grupo-de-recursos>` con el nombre de grupo de recursos que estás intentando eliminar.

Aparecerá una petición de confirmación:

```output
Are you sure you want to perform this operation? (y/n):
```

Presiona `y` para confirmar y eliminar el grupo de recursos.

Tomará un rato para eliminar todos los servicios.

Puedes leer más acerca de la eliminación de grupos de recursos en la [documentación de Azure para administración y eliminación de grupos de recursos)[https://docs.microsoft.com/azure/azure-resource-manager/management/delete-resource-group?WT.mc_id=academic-17441-jabenn&tabs=azure-cli]
