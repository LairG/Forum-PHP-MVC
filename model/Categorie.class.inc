<?php

class categorie {

    private $idCategorie;
    private $titreCategorie;
    private $descriptionCategorie;
    private $idAuteur;

    function __construct($idCategorie, $titreCategorie, $descriptionCategorie, $idAuteur) {
        $this->idCategorie = $idCategorie;
        $this->titreCategorie = $titreCategorie;
        $this->descriptionCategorie = $descriptionCategorie;
        $this->idAuteur = $idAuteur;
    }

    function getIdCategorie() {
        return $this->idCategorie;
    }

    function getTitreCategorie() {
        return $this->titreCategorie;
    }

    function getDescriptionCategorie() {
        return $this->descriptionCategorie;
    }

    function getIdAuteur() {
        return $this->idAuteur;
    }

    function setIdCategorie($idCategorie) {
        if (is_int($idCategorie)) {
            $this->idCategorie = $idCategorie;
        } else {
            throw new Exception('L\'id de la catégorie doit être un entier');
        }
    }

    function setTitreCategorie($titreCategorie) {
        $titreCategorie = trim($titreCategorie);
        $titreCategorie = strip_tags($titreCategorie);

        if (is_string($titreCategorie) && $titreCategorie != '') {
            $this->titreCategorie = substr($titreCategorie, 0, 49);
        } else {
            throw new Exception('Le titre de la catégorie doit être une chaine non vide');
        }
    }

    function setDescriptionCategorie($descriptionCategorie) {
        $descriptionCategorie = trim($descriptionCategorie);
        $descriptionCategorie = strip_tags($descriptionCategorie, '<b><strong><i><em><u><ul><li><ol>');
        $descriptionCategorie = str_replace(' ', '&nbsp;', $descriptionCategorie);
        $descriptionCategorie = nl2br($descriptionCategorie);
        if (is_string($descriptionCategorie) && $descriptionCategorie != '') {
            $this->descriptionCategorie = $descriptionCategorie;
        } else {
            throw new Exception('Le corps de la catégorie doit être une chaine non vide');
        }
    }

    function setIdAuteur($idAuteur) {
        if (is_int($idAuteur)) {
            $this->idAuteur = $idAuteur;
        } else {
            throw new Exception('L\'id de l\'auteur doit être un entier');
        }
    }
    public function formatCategorieForindex(){
        
        $html = '<div class="table-responsive" style="margin-top: 2rem;"><table class="table" style="background: linear-gradient(white, #E6F3F7);"><tr><td>';
        $html.= '<a href=topic.php?idcat='.$this->getIdCategorie().'>'.$this->getTitreCategorie().'</a>';
        $html.= '</td><td>Modéré par '. CategorieRepo::getInstance()->getPseudoUserCategorie($this->getIdCategorie());
        $html.= '</td><td><ul><li>Dernier post de ';
        $html.= CategorieRepo::getInstance()->getPseudoLastPost($this->getIdCategorie());
        $html.= '</li></br><li>';
        $html.= 'Le '. CategorieRepo::getInstance()->getDatelastPost($this->getIdCategorie());
        $html.= '</li></ul></td><td><ul><li>';
        $html.= CategorieRepo::getInstance()->getNbTopics($this->getIdCategorie()) . ' topics';
        $html.= '</li></br><li>';
        $html.= CategorieRepo::getInstance()->getNbPosts($this->getIdCategorie()) . ' posts';
        $html.= '</li></ul></td></tr><tr><td>';
        $html.= $this->getDescriptionCategorie();
        $html.= '</td></tr></table>';
        return $html;
    }
}
