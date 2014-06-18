/* Function to select a text in textarea with a click */
function select(text)
{
     var t = document.getElementById(text).innerHTML;
     alert(t);
}

/* Function to submit a form with a Enter button */
function send(t, e) 
{
    if (e.keyCode == 13)
    {
        t.form.submit();
    }
}