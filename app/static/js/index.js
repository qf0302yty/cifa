// $("#randomPlaceButton").click(function(){
//         $.ajax({
//         url: urlRandomPlace, 
//         type: "POST",
//         dataType: "json", 
//         error: function(data) {
//         	 alert(data);
//         	   },
//         success: function(data){
//             console.log(data);
//             var newhtml = "";        
//             newhtml+="<p class=\"p2\">"+data.name+"</p>";
//             newhtml+="<img src=\"/eat/Public/ace/assets/images/"+data.picture+"\" style=\"max-height:300px;\" alt=\"暂无\">";
//             $("#result1").html(newhtml);
//         }  
//   });  
// });

// $("#randomRestaurantButton").click(function(){
//         $.ajax({
//         url: urlRandomRestaurant, 
//         type: "POST",
//         dataType: "json", 
//         data:$('#randomRestaurantForm').serialize(),
//         error: function(data) {
//              alert(data);
//                },
//         success: function(data){
//             console.log(data);
//             var newhtml = "";        
//             newhtml+="<p class=\"p2\">"+data.name+"</p>";
//             newhtml+="<img src=\"/eat/Public/ace/assets/images/"+data.picture+"\" style=\"max-height:300px;\" alt=\"暂无\">";
//             $("#result2").html(newhtml);
//         }  
//   });  
// });