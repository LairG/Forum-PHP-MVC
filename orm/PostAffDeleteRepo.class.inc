<?php
    require_once 'orm/AbstractRepo.class.inc';
    require_once 'model/Post.class.inc';
    

    class PostAffDeleteRepo extends AbstractRepo
    {
        private static $instance;
        
        public static function getInstance()
        {
            if(isset(self::$instance))
            {
               return self::$instance; 
            }else
            {
                self::$instance = new PostAffDeleteRepo(); 
                return self::$instance;
            }     
        }//fin de getInstance
        
        
        protected function __construct() {
            parent::__construct();
        }
        
        
        
        //PB 23/11/15  Requette pour lire l'ensemble des post en fonction d'une catégorie trié par Date
        public function getAllPostByCategorieByDate($id_categorie,$id_ssCategorie='',$nbLimite,$numPage)
        {  
            $resultat       = array();
            $res            = "";
            $limitResult    = "";
            $pagination     = "";
            $cpt            = "";
            $returnVal      = array();
            
            //PB 24/11/15 Construction de m'a limite de page'
                 
            if($numPage != '' && is_numeric($numPage))
            { 
                $numPage = "LIMIT " . ($numPage - 1) * $nbLimite  . " , " . $nbLimite ;
            }  else {
                if(is_numeric($nbLimite))
                {
                    $numPage = "LIMIT 0 , " . $nbLimite ;    
                }
            }
 
            //PB 24/11/15 Lecture de l'ensemble des éléments sans aucune limite pour faire la pagination
            if ($id_ssCategorie != '' )
            {
                $sql = "SELECT * FROM post WHERE id_topic = " . $id_categorie . " AND id_ssCategorie = " . $id_ssCategorie . " ORDER BY date_post DESC";
            }else{
                $sql = "SELECT * FROM post WHERE id_topic = " . $id_categorie . " ORDER BY date_post DESC ";
            }
           
            $res = $this->getDb()->prepare($sql);
            $res->execute();
            $nbResult = $res->rowCount();     
            //PB 24/11/15 FIN DU COMPTAGE
            
            
            //PB 24/11/15 Je  vais devoir faire 2 fois la meme requete : UNE avec une limit et l'autre sans LIMIT pour connaitre le nombre de page au total'
            if ($id_ssCategorie != '' )
            {
                $sql = "SELECT * FROM post WHERE id_topic = " . $id_categorie . " AND id_ssCategorie = " . $id_ssCategorie . " ORDER BY date_post DESC" . $numPage;
            }else{
                $sql = "SELECT * FROM post WHERE id_topic = " . $id_categorie . " ORDER BY date_post DESC " . $numPage;
            }           
            
            $res = $this->getDb()->prepare($sql);
            $res->execute();
            //var_dump($nbResult);
            $resultat = $res->fetchALL();
            if($resultat != '')
            {
                
                //PB 24/11/15 Mtn que j'ai bien à la fois m'a limite donnée par le client et le nombre de résultat
                //je vais pouvoir construire la pagination
                $pagination = "";
                $cpt        = 0;
                if ($nbLimite != '')
                {
                    $tmpNbP = $nbResult / $nbLimite;
                    $tmpNbP = ceil($tmpNbP);
                    
                   // $pagination .= '<div style="color: red !important;">';
                    
                    for($i = 0; $i < $tmpNbP; $i++)
                    {
                        $cpt++;
                        $pagination .= '<a style="text-decoration: none;" class=pagination href=post.php?idtopic='.$id_categorie.'&limite='  . $nbLimite . '&page=' . $cpt .  '>' . $cpt .  '  &nbsp;&nbsp;\&nbsp;&nbsp;  ' . '</a>';    
                    }
                    
                   // $pagination .= '</div>';
                    
                }
                $returnVal['rSql'] = $resultat;
                $returnVal['pagination'] = $pagination;
                return $returnVal;
          
            }else{
                return false;
            } 
        }
        
       
        
       //PB 23/11/15 fonction qui permet d'afficher l'ensemble des post ) partir d'un tableau  
       public function affichePost($tableau,$tmpIdTopic,$tmpLimite,$tmpPage)
       {
           $result  = "";                        // PB 23/11/15 je vide ici la variable pour etre tranquille si pas de result
           if ($tableau != '')
           {
                foreach($tableau as $key => $value )  // PB 23/11/15 je boucle pour afficher chaque resultats
                { 

                 $sql = "SELECT nom FROM user WHERE id_user = " .  $value['id_user'];
                 $res = $this->getDb()->prepare($sql);
                 $res->execute();
                 $tmpAuteur = $res->fetch();

                 $result .= "<br/><table id='tabPost'><tr>";
                 $result .= "<thead id='theadPost'><th>" . $tmpAuteur[0] . "</th>"; //Lire si l'auter existe et recup son nom
                 $result .= "<th class='rightPost'>" . strftime('%d-%m-%Y',strtotime($value['date_post'])) . "</th></thead>";  // mettre la date en forme
                 $result .= "</tr>";  

                 $result .= '<tbody><td><div><a href=post.php?limite='.$tmpLimite.'&page='.$tmpPage.'&idtopic='.$tmpIdTopic.'&action=1&id=' . $value['id_post'] . '>Editer</a></div><br/><div><a href=post.php?limite='.$tmpLimite.'&page='.$tmpPage.'&idtopic='.$tmpIdTopic.'&action=2&id=' . $value['id_post'] . '>Supprimer</a></div></td>';
                 $result .= "<td class='centerPost'>" . $value['contenu'] . "</td></tbody>";
                 $result .= "</tr></table> <br/>";
                } 

                if ($result != '')
                {
                    return $result;
                } 
           }
       }
        
        
        // PB 24/11/15 Fonction qui me permet de lire juste un seul post
        public function readOnlyPost($id_Post)  
        {   
            if($id_Post != '' && (is_numeric($id_Post)))
            {
                $sql        =   "SELECT * FROM post WHERE id_post=:id_post";
                $rSql       =   $this->getDb()->prepare($sql);
                $rSql->execute(array('id_post' => $id_Post));
                $rSqlResult =   $rSql->fetch();
                
                
                if($rSqlResult != '')
                {
                    return $rSqlResult;
                }else{
                    return '';
                } 
            }
        }
      
        //24/11/15 Suppression d'un post -
        // A FAIRE : Gestion de la suppresion en fonction des droits
        public function deleteOnlyPost($id_Post)
        {
            if($id_Post != '' && (is_numeric($id_Post)))
            {
                $sql        =   "DELETE FROM post WHERE id_post=:id_post";
                $rSql       =   $this->getDb()->prepare($sql);
                $rSql->execute(array('id_post' => $id_Post ));
                $rSqlResult =   $rSql->rowCount(); 
                  
            }   
        }
        
        
          
    }   //FIN DE LA CLASS
    
    
   
?>