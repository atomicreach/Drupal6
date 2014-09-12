<?php

/*
 * Display AtomicReach assessment results.
 * Following class takes the Json formatted result and display it in human friendly format.
 * See: ../index.php From Line#90 to call each method.
 * Please take backup before you edit this file.
 * 
 */

class meta {

    private $result;
    private $targetAud;
    // Contructor getting result from ARClient.php in a form of an object.
    Public function __construct($obj, $targetAud) {
        $this->result = $obj;
        $this->targetAud = $targetAud;
    }

    /*     * *************************** */
    /* Content Sophistication    */
    /* find out more about this:   */
    /* http://www.slideshare.net/atomicreach/how-to-achieve-a-content-sophistication-match-for-your-audience */
    /*     * *************************** */

    /*     * **   SUMMARY TAB    *** */

    public function summaryTab() {
        $out = '<h3>TOP 3 OPPORTUNITIES</h3>
					<ul class="threeOpp ar_spritelist">';

        $stopAtThree = 0;
        $measState = $this->result->data->analysis;


        // 1 check audience match
        if ($measState->so->state !== 'green' && $stopAtThree != 3) {
            $out .= '<li class="ar_checkmarks_' . (($measState->so->state === "yellow") ? 'warning' : 'error') . '">
								Your post is not an audience match. Hit AUDIENCE to find out why.</li>';
            $stopAtThree++;
        }
        // 2 check if title is not green.
        if ($measState->tm->state !== 'green' && $stopAtThree != 3) {
            $out .= '<li class="ar_checkmarks_' . (($measState->tm->state === "yellow") ? 'warning' : 'error') . '">
								Your title needs work. Hit TITLE to find out why.</li>';
            $stopAtThree++;
        }
        // 3 check length
        if ($measState->ln->state !== 'green' && $stopAtThree != 3) {
            $out .= '<li class="ar_checkmarks_' . (($measState->ln->state === "yellow") ? 'warning' : 'error') . '">
								  Length of post is not optimal. Hit STRUCTURE to find out why.</li>';
            $stopAtThree++;
        }
        // 4 Check Grammar
        if ($measState->gm->state !== 'green' && $stopAtThree != 3) {
            $out .= '<li class="ar_checkmarks_' . (($measState->gm->state === "yellow") ? 'warning' : 'error') . '">
								Improve your grammar. Hit LINGUISTICS to find out how.</li>';
            $stopAtThree++;
        }
        // 4.5 Check Paragraph Word Density
        if ($measState->pwd->state !== 'green' && $stopAtThree != 3) {
            $out .= '<li class="ar_checkmarks_' . (($measState->pwd->state === "yellow") ? 'warning' : 'error') . '">
								Some of your paragraphs are too long for your target audience. Hit STRUCTURE to find out how.</li>';
            $stopAtThree++;
        }
        // 5 check if emotion is not green
        if ($measState->em->state !== 'green' && $stopAtThree != 3) {
            $out .= '<li class="ar_checkmarks_' . (($measState->em->state === "yellow") ? 'warning' : 'error') . '">
								Your post lacks emotion. Hit AUDIENCE to fix it.</li>';
            $stopAtThree++;
        }
        // 6 Check Spelling
        if ($measState->sm->state !== 'green' && $stopAtThree != 3) {
            $out .= '<li class="ar_checkmarks_' . (($measState->sm->state === "yellow") ? 'warning' : 'error') . '">
								Incorrect spelling detected. Hit LINGUISTICS to find out why.</li>';
            $stopAtThree++;
        }
        // 7 Links
        if ($measState->lc->state !== 'green' && $stopAtThree != 3) {
            $out .= '<li class="ar_checkmarks_' . (($measState->lc->state === "yellow") ? 'warning' : 'error') . '">
								Some links aren\'t working. Hit LINGUISTICS to find out more.</li>';
            $stopAtThree++;
        }
        // 8 Check Topics
        /* if($measState->tpp->state !== 'green' && $stopAtThree != 3){
          echo '';
          $stopAtThree ++;
          } */

        $out .= '</ul>';

        return $out;
    }

    public function contentSophistication() {
        $num = 0;
        $so = $this->result->data->analysis->so;
        $out = '<div class="' . $this->DOMsort($so->state) . '">' . PHP_EOL;
        $out .= '<input id="so" name="so" type="checkbox" />' . PHP_EOL;
        $out .= '<label for="so" id="ar-' . $so->state . '">Content Sophistication</label>' . PHP_EOL;
        $out .= '<article class="ac-large">' . PHP_EOL;
        $out .= '<p class="ar-analysis-' . $so->state . '">Your content is ' . $so->detail . ' for your audience</p>' . PHP_EOL;
//    $out .= '<ul class="details paragraph-sophistication">' . PHP_EOL;

        if (!empty($so->paragraphs)) {
            if ($so->detail === 'TOO SIMPLE') {
                $ar_message = 'Your article is too simple for your audience. To get the most of your content, 85% of your paragraphs need to be a match. Consider revising some of your highlighted paragraphs by writing longer sentences and using sophisticated language.';
            } elseif ($so->detail === 'TOO COMPLEX') {
                $ar_message = 'Your article is too complex for your audience. To get the most of your content, 85% of your paragraphs need to be a match. Consider revising some of your highlighted paragraphs by writing shorter sentences and simplifying your language.';
            }
            $ar_message .= '<p><a class="toggle-link ar-message-link" target="_blank" href="http://hub.atomicreach.com/i/303975/">Refer to our tips on how to achieve a content sophistication match for your audience <span>here</span></a>.</p>';
            $out .= $ar_message . PHP_EOL;
        }
//    $out .= '</ul>';
        $out .= '</article>' . PHP_EOL;
        $out .= '</div>' . PHP_EOL;
        return $out;
    }

    /*     * ************************** */
    /*   Underperforming Count    */
    /*     * ************************** */

    public function linkCount() {
        $lc = $this->result->data->analysis->lc;
        $out = '<div class="' . $this->DOMsort($lc->state) . '">' . PHP_EOL;
        $out .= '<input id="lc" name="lc" type="checkbox" />' . PHP_EOL;
        $out .= '<label for="lc" id="ar-' . $lc->state . '">Underperforming Link(s)</label>' . PHP_EOL;
        $out .= '<article class="ac-small">' . PHP_EOL;
        $out .= '<p class="ar-analysis-' . $lc->state . '">';
        if ($lc->invalid >= 1) {
            if ($lc->invalid == 1) {
                $verb = 'is';
            } else {
                $verb = 'are';
            }
            $out .= $lc->invalid . ' out of the ' . $lc->total . ' links included in the posts ' . $verb . ' underperforming' . PHP_EOL;
            $out .= '<ul class="invalid-links">';
            foreach ($lc->detail AS $links) {
                $out .= '<li><a href="' . $links . '" target="_blank"><span class="ilText">' . $links . '</span></a></li>' . PHP_EOL;
            }
            $out .= '</ul>';
        } else {
            $out .= 'All links are valid';
        }
        $out .= '</p>' . PHP_EOL;
        $out .= '</article>' . PHP_EOL;
        $out .= '</div>' . PHP_EOL;
        return $out;
    }

    /*     * ******************** */
    /*   Content Length     */
    /*     * ******************** */

    public function contentLength() {
        $ln = $this->result->data->analysis->ln;
        $out = '<div class="' . $this->DOMsort($ln->state) . '">' . PHP_EOL;
        $out .= '<input id="ln" name="ln" type="checkbox" />' . PHP_EOL;
        $out .= '<label for="ln"  id="ar-' . $ln->state . '">Content Length</label>' . PHP_EOL;
        $out .= '<article class="ac-small">' . PHP_EOL;
        $out .= '<p class="ar-analysis-' . $ln->state . '">';
//    if ($ln->state == 'green') {
        $out .= 'length of post is ' . $ln->measured->sentences . ' sentences. For text based posts our recommended range is ' . $ln->recommended->sentencesMin . '-' . $ln->recommended->sentencesMax . ' sentences for greater engagement.';
//    } else {
//      $out .= 'length of post is ' . $ln->measured->sentences . ' sentences. For text based posts our recommended range is 25-75 sentences for greater engagement.';
//    }
        $out .= '</p>' . PHP_EOL;
        $out .= '</article>' . PHP_EOL;
        $out .= '</div>' . PHP_EOL;
        return $out;
    }

    /*     * *************************  */
    /*     Paragraph Density           */
    /*     * ******************************* */

    public function paragraphDensity() {
        $pwd = $this->result->data->analysis->pwd;

        // states: passed (green) - warning (yellow) - error (red)
        $ms = 100 - $pwd->measured->percentageParagraphsIdealWordCountMetadata;
        //$pwdMin = $pwd->recommended->paragraphWordDensityMin;
        $pwdMax = $pwd->recommended->paragraphWordDensityMax;
        // $state = arnanlyzer_rsl_state($ms, $rs);
        $state = strtolower($pwd->state);

        $out = '<div class="' . $this->DOMsort($state) . '">' . PHP_EOL;
        $out .= '<input id="pwd" name="pwd" type="checkbox" />' . PHP_EOL;
        $out .= '<label for="pwd"  id="ar-' . $state . '">Paragraph Density</label>' . PHP_EOL;
        $out .= '<article class="ac-small">' . PHP_EOL;
        $out .= '<p class="ar-analysis-' . $state . '">';
        if ($state == 'green') {
            $out .= '<div>Your paragraphs are an ideal length for your target audience.</div>';
        } else {
            $out .= '<div>' . $ms . '% of your paragraphs are too long for your target audience. Write paragraphs with no greater than ' . $pwdMax . ' words.</div>';
        }
        $out .= '</p>' . PHP_EOL;
        $out .= '</article>' . PHP_EOL;
        $out .= '</div>' . PHP_EOL;
        return $out;
    }

    /*     * ************************ */
    /*   Content Originality    */
    /*     * ************************ */

    public function contentOriginality() {
        $su = $this->result->data->analysis->su;
        $out = '<div class="' . $this->DOMsort($su->state) . '">' . PHP_EOL;
        $out .= '<input id="su" name="su" type="checkbox" />' . PHP_EOL;
        $out .= '<label for="su" id="content-orginality">Content Originality</label>' . PHP_EOL;
        $out .= '<article class="ac-small">' . PHP_EOL;
        $out .= '<p class="ar-analysis-' . $su->state . '">';
        if ($su->state == 'green') {
            $msg = '<img class="ar-thumbsUp" src="' . $base_url . '/sites/all/modules/atomicreach/images/thumbs_up.png">Your content is unique and will drive engagement, so share away!';
        } else {
            $msg = 'Original content drives more engagement. We will alert you when your content is unique.';
        }
        $out .= $msg;
        $out .= '</p>' . PHP_EOL;
        $out .= '</article>' . PHP_EOL;
        $out .= '</div>' . PHP_EOL;
        return $out;
    }

    /*     * ************************ */
    /*     Content Emotion      */
    /*     * ************************ */

    public function contentEmotion() {
        $em = $this->result->data->analysis->em;
        if ($em->state == 'red') {
            $colour = 'yellow';
        } else {
            $colour = $em->state;
        }
        $out = '<div class="' . $this->DOMsort($colour) . '">' . PHP_EOL;
        $out .= '<input id="em" name="em" type="checkbox" />' . PHP_EOL;
        $out .= '<label for="em"  id="ar-' . $colour . '">Content Emotion</label>' . PHP_EOL;
        $out .= '<article class="ac-large">' . PHP_EOL;
        $out .= '<p class="ar-analysis-' . $colour . '">';
//    $out .= $em->detail;
        $out .= '<ul class="emotion-details">';
        foreach ($em->dimensions as $key => $value) {
            $out .= '<li class="emotion-' . strtolower($value->state) . '"><strong>' . $value->name . '</strong>: ' . $value->detail . '</li>';
        }
        $out .= '<p>Refer to our tips on how to write with emotion <a class="toggle-link ar-message-link" target="_blank" href="http://hub.atomicreach.com/i/303948/"><span>here</span></a>.</p>';
        $out .= '</ul>';


        $out .= '</p>' . PHP_EOL;
        $out .= '</article>' . PHP_EOL;
        $out .= '</div>' . PHP_EOL;
        return $out;
    }

    /*     * ************************ */
    /*   Spelling Mistakes      */
    /*     * ************************ */

    public function spellingMistakes() {
        $sm = $this->result->data->analysis->sm;
        $out = '<div class="' . $this->DOMsort($sm->state) . '">' . PHP_EOL;
        $out .= '<input id="sm" name="sm" type="checkbox" />' . PHP_EOL;
        $out .= '<label for="sm"  id="ar-' . $sm->state . '">Spelling Mistakes</label>' . PHP_EOL;
        $out .= '<article class="ac-large">' . PHP_EOL;
        $out .= '<p class="ar-analysis-' . $sm->state . '">There ';
        $out .= ($sm->total == 1) ? 'is ' : 'are ';
        $out .= $sm->total . ' misspelled word(s).</p>' . PHP_EOL;
        if (count($sm->detail) > 0) {
            $out .= '<ul class="spelling-mistakes">';
            $out .= '<p>Hit the Spelling Mistakes button above to highlight these words in your article. Fix the ones that are incorrect or right click a word to add it to your custom dictionary.</p>';
            foreach ($sm->detail as $value) {
                $out .= '<li><span class="smText">' . $value->string . '</span><strong> Suggestions: </strong>';
                //if($result->data->analysis->sm->total > 0) {
                if (!empty($value->suggestions->option)) {
                    if (!is_array($value->suggestions->option)) {
                        $value->suggestions->option = array(
                            $value->suggestions->option
                        );
                    }
                    $suggestions = array();
                    foreach ($value->suggestions->option AS $v) {
                        array_push($suggestions, $v);
                    }
                    $out .= implode(", ", $suggestions);
                }
                //  }
                $out .= '</li>' . PHP_EOL;
            }
            $out .= '</ul>';
            $words = array();
            foreach ($sm->detail as $value)
                $words[] = $value->string;
            $out .= '<script type="text/javascript">
                         var SMwords = ' . json_encode($words) . ';
                         </script>';
        } // end if is array.
        $out .= '</article>' . PHP_EOL;
        $out .= '</div>' . PHP_EOL;
        return $out;
    }

    /*     * ************************ */
    /*    Grammar Mistakes      */
    /*     * ************************ */

    public function grammarMistakes() {
        $gm = $this->result->data->analysis->gm;
        $out = '<div class="' . $this->DOMsort($gm->state) . '">' . PHP_EOL;
        $out .= '<input id="gm" name="gm" type="checkbox" />' . PHP_EOL;
        $out .= '<label for="gm" id="ar-' . $gm->state . '">Grammar Insights</label>' . PHP_EOL;
        $out .= '<article class="ac-large">' . PHP_EOL;
        $out .= '<p class="ar-analysis-' . $gm->state . '">There ';
        $out .= ($gm->total == 1) ? 'is ' : 'are ';
        $out .= $gm->total . ' grammar error(s).</p>' . PHP_EOL;
        if (is_array($gm->detail)) {
            $out .= '<ul class="grammar-mistakes">';
            $out .= '<p>These grammatical recommendations will improve your post.</p>';
            foreach ($gm->detail as $value) {
                if (!empty($value->suggestions)) {
                    if (!is_array($value->suggestions)) {
                        $value->suggestions = array(
                            $value->suggestions
                        );
                    }
                }
                $out .= '<li><span class="gmText">' . $value->string . '</span> - <a href="' . $value->url . '" target="_blank">See Explanation</a></li>' . PHP_EOL;
            }


            $words = array();
            foreach ($gm->detail as $key => $value)
                $words[] = $value->string;
            $out .= '<script type="text/javascript">
                         var GMwords = ' . json_encode($words) . ';
                         </script>';



            $out .= '<p>Refer to our guide on how to write with an active voice <a class="toggle-link ar-message-link" target="_blank" href="http://hub.atomicreach.com/i/304278/"><span>here</span></a>.</p>';
            $out .= '</ul>';
        } // end if is array.
        $out .= '</article>' . PHP_EOL;
        $out .= '</div>' . PHP_EOL;
        return $out;
    }

    /*     * ****************** */
    /*    Topics Tags     */
    /*     * ****************** */

    public function topicsTags() {
        $tg = $this->result->data->analysis->tg;
        $out = '<div class="' . $this->DOMsort($tg->state) . '">' . PHP_EOL;
        $out .= '<input id="tg" name="accordion-1" type="checkbox" />' . PHP_EOL;
        $out .= '<label for="tg" id="ar-' . $tg->state . '">' . $tg->total . ' Keyword(s)</label>' . PHP_EOL;
        $out .= '<article class="ac-large">' . PHP_EOL;
        $out .= '<p class="ar-analysis-' . $tg->state . '">';
        if ($tg->total >= 1) {
            $out .= $tg->total . ' Keyword(s) identified. ' . PHP_EOL;
            $out .= '<ul>';
            $out .= '<p>These are your post\'s keywords. Use 1-4 terms in your title to optimize it!</p>';
            foreach ($tg->detail AS $tags) {
                $out .= '<li>' . $tags . '</li>' . PHP_EOL;
            }
            $out .= '</ul>';
        } else {
            $out .= '0 tags identified.';
        }
        $out .= '</p>' . PHP_EOL;
        $out .= '</article>' . PHP_EOL;
        $out .= '</div>' . PHP_EOL;
        return $out;
    }

    /*     * ************************ */
    /*   Content Clarity    */
    /*     * ************************ */

    public function contentClarity() {
        $lr = $this->result->data->analysis->lr;
        $out = '<div class="' . $this->DOMsort($lr->state) . '">' . PHP_EOL;
        $out .= '<input id="lr" name="lr" type="checkbox" />' . PHP_EOL;
        $out .= '<label for="lr"  id="ar-' . $lr->state . '">Content Clarity</label>' . PHP_EOL;
        $out .= '<article class="ac-small">' . PHP_EOL;
        $out .= '<p class="ar-analysis-' . $lr->state . '">';
        $out .= $lr->detail;
        $out .= '</p>' . PHP_EOL;
        $out .= '</article>' . PHP_EOL;
        $out .= '</div>' . PHP_EOL;
        return $out;
    }

    /*     * *********************** */
    /*   Title Optimization   */
    /*     * *********************** */

    public function titleOptimization() {
        $tm = $this->result->data->analysis->tm;
        $out = '<div class="' . $this->DOMsort($tm->state) . '">' . PHP_EOL;
        $out .= '<input id="tm" name="tm" type="checkbox" />' . PHP_EOL;
        $out .= '<label for="tm"  id="ar-' . $tm->state . '">Title Optimization</label>' . PHP_EOL;
        $out .= '<article class="ac-large">' . PHP_EOL;
        $out .= '<p class="ar-analysis-' . $tm->state . '">';
        $out .= "<strong>" . $tm->message . "</strong>";
        $out .= '</p>' . PHP_EOL;
        if ($tm->detail >= 0) {
            $num = 1;
            $out .= "<ul class='tm'>";
            foreach ($tm->recomendations AS $rec) {
                if (!empty($rec)) {
                    $out .= "<li>" . $rec . "</li>";
                    $num++;
                }
            }
            $out .= '<p>Refer to our guide on how to create engaging titles <a class="toggle-link ar-message-link" target="_blank" href="http://hub.atomicreach.com/i/303939/"><span>here</span></a>.</p>';
            $out .= "</ul>";
        }
        $out .= '</article>' . PHP_EOL;
        $out .= '</div>' . PHP_EOL;
        return $out;
    }

    public function displayHighlightsButtons() {
        if ($this->result->data->analysis->sm->total > 0 
                || $this->result->data->analysis->gm->total > 0 
                || $this->result->data->analysis->lc->invalid > 0 
                || strtolower($this->result->data->analysis->so->state !== 'green') 
                || strtolower($this->result->data->analysis->pwd->state !== 'green')):
            $out = '';
            $out .= '<strong>Select a category to highlight areas to refine:</strong>';
            $out .= '<ul class="hl-btns">';
            if ($this->result->data->analysis->sm->total > 0):
                $out .= '<li>';
                $out .= '<input type="checkbox" id="chksp" name="chk" value="all">
<label for="chksp">Spelling Mistakes</label>
</li>';
            endif;
            if ($this->result->data->analysis->gm->total > 0):
                $out .= '<li>   
<input type="checkbox" id="chkgm" name="chk"value="false">
<label for="chkgm">Grammar Mistakes</label>
</li>';
            endif;
            if ($this->result->data->analysis->lc->invalid > 0):
                $out .= '<li>   
<input type="checkbox" id="chkul" name="chk" value="true">
<label for="chkul">Underperforming Links</label>
</li>';
            endif;
            if (strtolower($this->result->data->analysis->so->state !== 'green')):
                $out .= '<li>   
<input class="' . strtolower(str_replace(" ", "-", $this->result->data->analysis->so->detail)) . '" type="checkbox" id="chkso" name="chk" value="false">
<label for="chkso">Audience Mismatch</label>
</li>';
                $light_blue = '#91c7f9';
                $light_orange = '#FFA20C';
                $out .= '<script type="text/javascript">
                         var tooSimpleColor = ' . json_encode($light_blue) . ';
                         var tooComplexColor = ' . json_encode($light_orange) . ';
                         var domExpression = ' . json_encode($this->result->data->analysis->so->paragraphDOM) . ';
                         var paragraphs = ' . json_encode($this->result->data->analysis->so->paragraphs) . ';
                         </script>';
            endif;
            // PARAGRAPH DENSITY
            if (strtolower($this->result->data->analysis->pwd->state !== 'green')):
                $out .= '<li>   
<input type="checkbox" id="chkpwd" name="chk" value="true">
<label for="chkpwd">Paragraph Density</label>
</li>';
                $out .= '
        <script>
        var PWDtooShortColor = ' . json_encode('#F6C9CB') . ';
        var PWDtooLongColor = ' . json_encode('#C98BD1') . ';
        var PWDparagraphs = ' . json_encode($this->result->data->analysis->pwd->detail->paragraphs) . ';
        var PWDdomExpression = ' . json_encode($this->result->data->analysis->pwd->detail->paragraphDOM) . ';
</script>';
            endif; // end parag density

            $out .= '</ul>   ';
            return $out;
        endif;
    }

    public function displayScore() {
        $score = $this->result->data->scoring;
        if ($score <= 50) {
            $msg = '<span style="color: #F72210;">Need Changes!</span>';
        } elseif ($score > 50 && $score < 75) {
            $msg = '<span style="color:  #F6D610;">Almost There!</span>';
        } elseif ($score >= 75) {
            $msg = '<span style="color:  #2ecc71;">On Your Way!</span>';
        }


        $out = '<div class="ar-score-wrapper">';
        $out .= '<div class="ar-score-container"><span>' . $score . '</span></div>';


        if ($this->result->data->analysis->so->detail == 'TOO COMPLEX') {
            $pieImg = 'AR-TooComplicated.png';
        } elseif ($this->result->data->analysis->so->detail == 'TOO SIMPLE') {
            $pieImg = 'AR-TooSimple.png';
        } elseif ($this->result->data->analysis->so->detail == 'HIT') {
            if ($this->targetAud == 'GENERAL') {
                $pieImg = 'AR-Match-General.png';
            } elseif ($this->targetAud == 'KNOWLEDGEABLE') {
                $pieImg = 'AR-Match-Knowledgable.png';
            } elseif ($this->targetAud == 'ACADEMIC') {
                $pieImg = 'AR-Match-Academic.png';
            } elseif ($this->targetAud == 'SPECIALIST') {
                $pieImg = 'AR-Match-Specialist.png';
            } elseif ($this->targetAud == 'GENIUS') {
                $pieImg = 'AR-Match-Genius.png';
            }
        }

        $out .= '<img src="' . base_path() . drupal_get_path('module', 'atomicreach') . '/inc/images/' . $pieImg . '" alt="soph pie img" />';
        $out .= '</div>';


        $out .= '<p class="ar-msg">Aim for an Atomic Score of 60+, but with the suggestions below you can gain even greater engagement.</p>';

//        $out .= '<div class="ar-progress">';
        //        $out .= '<div class="ar-bar bar-danger" style="width: 50%;"></div>';
        //        $out .= '<div class="ar-bar bar-warning" style="width: 30%;"></div>';
        //        $out .= '<div class="ar-bar bar-success" style="width: 20%;"></div>';
        //        $out .= '<div class="ar-score" style="left:' . $score . '%;"><i class="fa fa-long-arrow-up"></i></div>';
        //        $out .= '<div class="ar-score-message">' . $msg . '</div>';
        return $out;
    }

    public function displayResult() {
        return $this->result;
    }

    public function DOMsort($state) {
        if (strtolower($state) == "green") {
            return "3";
        } else if (strtolower($state) == "yellow") {
            return "2";
        } else if (strtolower($state) == "red") {
            return "1";
        }
    }

    public function atomicScore() {
        return $this->result->data->scoring;
    }

}
?>