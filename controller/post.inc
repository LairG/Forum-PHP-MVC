<?php

$idPost     = (isset($_POST['id_post_hidden']))?intval($_POST['id_post_hidden']):(-1);
$datePost   = (isset($_POST['nouvelle_date_post']))?($_POST['nouvelle_date_post']):('');
$idAuteurPost = (isset($_POST['auteur_post']))?intval($_POST['auteur_post']):('');
$contenuPost= (isset($_POST['contenu_post']))?($_POST['contenu_post']):('');
$submit_ok  = isset($_POST['submit_post']);

//PB 24/11/15 Ajout des 2 éléments pour EDITER OU SUPPRIMER un post
$action     = ( isset($_GET['action']) && !empty($_GET['action'])) ? $_GET['action'] : ('');
$id         = ( isset($_GET['id']) && !Empty($_GET['id']) ) ? $_GET['id'] : ('');
$limite     = ( isset($_GET['limite']) && !empty($_GET['limite'])) ? $_GET['limite'] : ('');
$page       = ( isset($_GET['page']) && !empty($_GET['page'])) ? $_GET['page'] : ('');
//$id_topic = "";
$id_topic       = ( isset($_GET['idtopic']) && !empty($_GET['idtopic'])) ? $_GET['idtopic'] : ('');
//PB FIN


$form_ok        = true;
$error_msg      = '';
$retourTableau  = "";
$retourValeur   = array();
$paginationPost = "";

$tmpContenu = "";
$tmpDate    = "";
$tmpIdUser  = "";
$tmpId_Post = "";

$postRepo = PostAffDeleteRepo::getInstance();

switch ($action) {
    case 1:             // si je suis dans le cas 1 alors je vais mettre les infos dans le formulaire
         
   
        $rTableau = $postRepo->readOnlyPost($id);
        
        if($rTableau != '')
        {  
           $tmpId_Post =    $rTableau['id_post'];
           $tmpContenu =    $rTableau['contenu'];    
           $tmpDate    =    $rTableau['date_post'];  
           $tmpIdUser  =    $rTableau['id_user'];    
        }        
        
        break;
        
    case 2:             // je suppirme le post
        $postRepo->deleteOnlyPost($id);
        break;
    
    default:
        break;
}

//update ou insert dans la bd, selon le "idPost" recuperé
if($submit_ok) {
    try {
            $user = new User($idAuteurPost, 'aaa', 'e3b98a4da31a127d4bde6e43033f66ba274cab0eb7eb1c70ec41402bf6273dd8', 'aaa', 'aaa', '2012-12-12', '0123456789', 'toto@toto.fr', 0);
            $topic = new Topic($idAuteurPost, 'toto', 0, 0);
            $postEditRepo = PostEditRepo::getInstance();  
            $newPost = new Post($idPost, $user, $topic, $datePost, $contenuPost);
            var_dump($newPost);
            if($idPost == -1 ){               
                $postEditRepo->insertPost($newPost); 
            } else {
                $postEditRepo->updatePost($newPost);
            }           
    } catch(Exception $e) {
            $error_msg .= $e->getMessage();
            var_dump($e);
    }
}

//Affichage de l'ensemble des post
//$postRepo       = PostAffDeleteRepo::getInstance();

$tableauRes     = $postRepo->getAllPostByCategorieByDate($id_topic,'',$limite,$page);
$retourValeur   = $postRepo->affichePost($tableauRes['rSql'],$id_topic,$limite,$page);

//$retourTableau  = $tableauRes['rSQL'];
$paginationPost = $tableauRes['pagination'];

?>