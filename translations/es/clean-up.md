<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "5a94fbab1ba737e9bd6cc6c64f114fa0",
  "translation_date": "2025-08-26T13:57:07+00:00",
  "source_file": "clean-up.md",
  "language_code": "es"
}
-->
# Limpia tu proyecto

Después de completar cada proyecto, es una buena práctica eliminar tus recursos en la nube.

En las lecciones de cada proyecto, es posible que hayas creado algunos de los siguientes:

* Un Grupo de Recursos  
* Un IoT Hub  
* Registros de dispositivos IoT  
* Una Cuenta de Almacenamiento  
* Una Aplicación de Funciones  
* Una cuenta de Azure Maps  
* Un proyecto de visión personalizada  
* Un Registro de Contenedores de Azure  
* Un recurso de servicios cognitivos  

La mayoría de estos recursos no tendrán costo: o son completamente gratuitos, o estás utilizando un nivel gratuito. Para los servicios que requieren un nivel de pago, los habrías estado utilizando en un nivel incluido en la asignación gratuita, o solo te costarán unos pocos centavos.

Incluso con costos relativamente bajos, vale la pena eliminar estos recursos cuando termines. Por ejemplo, solo puedes tener un IoT Hub utilizando el nivel gratuito, por lo que si deseas crear otro, necesitarás usar un nivel de pago.

Todos tus servicios se crearon dentro de Grupos de Recursos, lo que facilita su gestión. Puedes eliminar el Grupo de Recursos, y todos los servicios dentro de ese Grupo de Recursos se eliminarán junto con él.

Para eliminar el Grupo de Recursos, ejecuta el siguiente comando en tu terminal o línea de comandos:

```sh
az group delete --name <resource-group-name>
```

Sustituye `<resource-group-name>` por el nombre del Grupo de Recursos que te interesa.

Aparecerá una confirmación:

```output
Are you sure you want to perform this operation? (y/n): 
```

Introduce `y` para confirmar y eliminar el Grupo de Recursos.

Eliminar todos los servicios tomará un tiempo.

> 💁 Puedes leer más sobre cómo eliminar grupos de recursos en la [documentación sobre eliminación de grupos de recursos y recursos del Administrador de Recursos de Azure en Microsoft Docs](https://docs.microsoft.com/azure/azure-resource-manager/management/delete-resource-group?WT.mc_id=academic-17441-jabenn&tabs=azure-cli)

---

**Descargo de responsabilidad**:  
Este documento ha sido traducido utilizando el servicio de traducción automática [Co-op Translator](https://github.com/Azure/co-op-translator). Si bien nos esforzamos por garantizar la precisión, tenga en cuenta que las traducciones automatizadas pueden contener errores o imprecisiones. El documento original en su idioma nativo debe considerarse la fuente autorizada. Para información crítica, se recomienda una traducción profesional realizada por humanos. No nos hacemos responsables de malentendidos o interpretaciones erróneas que puedan surgir del uso de esta traducción.