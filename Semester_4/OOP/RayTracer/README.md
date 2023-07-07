infos pour les dev

si vous voulez creer une nouvelle release de raytracer EXEMPLE commande a faire:
(utiliser un folder complet existant comme src et un non existant en target)
./bin/UpdatePlugin sources/RayTracing/RayCasting ./sources/RayTracing/Plugins/patate


pour moi:

finir la gestion des farmer worker
il faut gerer les changements d'informations impoortant comme un changement de config
il faut gerer la facon dont on envoit les data aux clients
normalement la gestion du travail se fait maintenant seul dans les clients
faire fonctionner la demande de travail du client
il faut gerer la reception des datas par le serveur
j'ai pls d'idee mais il doit manquer 2/3 trucs

mettre un select avec timeout sur le thread important infos du client pour qu'il repasse dans la variable conditionnel