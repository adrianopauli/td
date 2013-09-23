function sendComand(comando){
	 $.ajax({
        url: "http://localhost:8000/ajax/ir/",
        dataType: "text",
        data:{'comando':comando},
        error: function(XMLHttpRequest, textStatus, errorThrown) {
            alert(errorThrown);
        },
        success: function(data, textStatus, XMLHttpRequest) {
            alert(data)
        }
    });

}