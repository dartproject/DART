<html>
<head>
	<script src=\"http://localhost/dart/lib/utility.txt\"></script>
	<script type=\"text/javascript\" src=\"http://localhost/dart/lib/myScript.js\"></script>
</head>
<body>
<form>
<input type="button" value="Add" onclick="addRowClone('phoneClone');" />				
<table id="phoneClone" class="graybg">
	<thead>
	<tr class="bluebarsub"><td></td><td>Action</td><td>Person</td><td>Type</td><td>Timeline</td><td>Evaluation</td><td>Final Outcome</td></tr>
	</thead>
	<tr>	<td>D</td>
					<td><input size = 10 type=text id=action value="" /></td>
					<td><input  size = 7 type=text id=person value="" /></td>
					<td><select id="type"><option>teacher</option><option>parent</option><option>staff</option></select></td>
					<td><input  size = 7 type=text id=Timeline value="" /></td>
					<td><input  size = 12 type=text id=evaluation value="" /></td>
					<td><input  size = 12 type=text id=final value="" /></td>		
	</tr>
</table>
</form>
</body>
</html>
