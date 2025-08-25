<!--
CO_OP_TRANSLATOR_METADATA:
{
  "original_hash": "24dc783a600e20251211987b36370e93",
  "translation_date": "2025-08-24T21:45:56+00:00",
  "source_file": "4-manufacturing/lessons/3-run-fruit-detector-edge/vm-iotedge.md",
  "language_code": "fr"
}
-->
# Créer une machine virtuelle exécutant IoT Edge

Dans Azure, vous pouvez créer une machine virtuelle - un ordinateur dans le cloud que vous pouvez configurer comme vous le souhaitez et sur lequel vous pouvez exécuter vos propres logiciels.

> 💁 Vous pouvez en savoir plus sur les machines virtuelles sur la [page Wikipédia des machines virtuelles](https://wikipedia.org/wiki/Virtual_machine).

## Tâche - Configurer une machine virtuelle IoT Edge

1. Exécutez la commande suivante pour créer une machine virtuelle avec Azure IoT Edge déjà préinstallé :

    ```sh
    az deployment group create \
                --resource-group fruit-quality-detector \
                --template-uri https://raw.githubusercontent.com/Azure/iotedge-vm-deploy/1.2.0/edgeDeploy.json \
                --parameters dnsLabelPrefix=<vm_name> \
                --parameters adminUsername=<username> \
                --parameters deviceConnectionString="<connection_string>" \
                --parameters authenticationType=password \
                --parameters adminPasswordOrKey="<password>"
    ```

    Remplacez `<vm_name>` par un nom pour cette machine virtuelle. Ce nom doit être globalement unique, donc utilisez quelque chose comme `fruit-quality-detector-vm-` suivi de votre nom ou d'une autre valeur.

    Remplacez `<username>` et `<password>` par un nom d'utilisateur et un mot de passe pour vous connecter à la machine virtuelle. Ces informations doivent être relativement sécurisées, vous ne pouvez donc pas utiliser admin/password.

    Remplacez `<connection_string>` par la chaîne de connexion de votre appareil IoT Edge `fruit-quality-detector-edge`.

    Cela créera une machine virtuelle configurée comme une machine virtuelle de type `DS1 v2`. Ces catégories indiquent la puissance de la machine, et donc son coût. Cette machine virtuelle dispose d'un processeur et de 3,5 Go de RAM.

    > 💰 Vous pouvez consulter les tarifs actuels de ces machines virtuelles sur le [guide des prix des machines virtuelles Azure](https://azure.microsoft.com/pricing/details/virtual-machines/linux/?WT.mc_id=academic-17441-jabenn)

    Une fois la machine virtuelle créée, le runtime IoT Edge sera installé automatiquement et configuré pour se connecter à votre IoT Hub en tant qu'appareil `fruit-quality-detector-edge`.

1. Vous aurez besoin de l'adresse IP ou du nom DNS de la machine virtuelle pour appeler le classificateur d'images depuis celle-ci. Exécutez la commande suivante pour obtenir cette information :

    ```sh
    az vm list --resource-group fruit-quality-detector \
               --output table \
               --show-details
    ```

    Copiez soit le champ `PublicIps`, soit le champ `Fqdns`.

1. Les machines virtuelles coûtent de l'argent. Au moment de la rédaction, une machine virtuelle DS1 coûte environ 0,06 $ par heure. Pour réduire les coûts, vous devriez éteindre la machine virtuelle lorsque vous ne l'utilisez pas et la supprimer une fois le projet terminé.

    Vous pouvez configurer votre machine virtuelle pour qu'elle s'éteigne automatiquement à une certaine heure chaque jour. Cela signifie que si vous oubliez de l'éteindre, vous ne serez facturé que pour le temps jusqu'à l'arrêt automatique. Utilisez la commande suivante pour configurer cela :

    ```sh
    az vm auto-shutdown --resource-group fruit-quality-detector \
                        --name <vm_name> \
                        --time <shutdown_time_utc>
    ```

    Remplacez `<vm_name>` par le nom de votre machine virtuelle.

    Remplacez `<shutdown_time_utc>` par l'heure UTC à laquelle vous souhaitez que la machine virtuelle s'éteigne, en utilisant 4 chiffres au format HHMM. Par exemple, si vous souhaitez un arrêt à minuit UTC, vous devez définir cette valeur sur `0000`. Pour 19h30 sur la côte ouest des États-Unis, vous utiliseriez `0230` (19h30 sur la côte ouest des États-Unis correspond à 2h30 UTC).

1. Votre classificateur d'images fonctionnera sur cet appareil Edge, en écoutant sur le port 80 (le port HTTP standard). Par défaut, les machines virtuelles ont les ports entrants bloqués, vous devrez donc activer le port 80. Les ports sont activés sur les groupes de sécurité réseau, vous devez donc d'abord connaître le nom du groupe de sécurité réseau de votre machine virtuelle, que vous pouvez trouver avec la commande suivante :

    ```sh
    az network nsg list --resource-group fruit-quality-detector \
                        --output table
    ```

    Copiez la valeur du champ `Name`.

1. Exécutez la commande suivante pour ajouter une règle permettant d'ouvrir le port 80 dans le groupe de sécurité réseau :

    ```sh
    az network nsg rule create \
                        --resource-group fruit-quality-detector \
                        --name Port_80 \
                        --protocol tcp \
                        --priority 1010 \
                        --destination-port-range 80 \
                        --nsg-name <nsg name>
    ```

    Remplacez `<nsg name>` par le nom du groupe de sécurité réseau de l'étape précédente.

### Tâche - Gérer votre machine virtuelle pour réduire les coûts

1. Lorsque vous n'utilisez pas votre machine virtuelle, vous devriez l'éteindre. Pour éteindre la machine virtuelle, utilisez la commande suivante :

    ```sh
    az vm deallocate --resource-group fruit-quality-detector \
                     --name <vm_name>
    ```

    Remplacez `<vm_name>` par le nom de votre machine virtuelle.

    > 💁 Il existe une commande `az vm stop` qui arrête la machine virtuelle, mais elle conserve l'ordinateur alloué à vous, ce qui signifie que vous continuez à payer comme si elle fonctionnait encore.

1. Pour redémarrer la machine virtuelle, utilisez la commande suivante :

    ```sh
    az vm start --resource-group fruit-quality-detector \
                --name <vm_name>
    ```

    Remplacez `<vm_name>` par le nom de votre machine virtuelle.

**Avertissement** :  
Ce document a été traduit à l'aide du service de traduction automatique [Co-op Translator](https://github.com/Azure/co-op-translator). Bien que nous nous efforcions d'assurer l'exactitude, veuillez noter que les traductions automatisées peuvent contenir des erreurs ou des inexactitudes. Le document original dans sa langue d'origine doit être considéré comme la source faisant autorité. Pour des informations critiques, il est recommandé de recourir à une traduction humaine professionnelle. Nous déclinons toute responsabilité en cas de malentendus ou d'interprétations erronées résultant de l'utilisation de cette traduction.