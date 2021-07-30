<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="2.0">

<!-- Get the start time (in milliseconds) -->
<xsl:variable name="START_TIME_MS">
	<xsl:value-of select="/log/record[position()=1]/millis"/>
</xsl:variable>

<!-- Get the end time (in milliseconds) -->
<xsl:variable name="END_TIME_MS">
	<xsl:value-of select="/log/record[last()]/millis"/>
</xsl:variable>

<!-- Stylesheet for Debug Server Logs  -->
<xsl:template match="/">

	<html>
		<body>
			<h2>Debug Server Log</h2>
			<h3>Total Execution Time: <xsl:value-of select="$END_TIME_MS - $START_TIME_MS"/> ms</h3>
			<xsl:apply-templates />
		</body>
	</html>
</xsl:template>

<xsl:template match="log">
	<table border="1">
		<tr bgcolor="#9acd32">
			<th>Sequence</th>
			<th>Time (ms)</th>
			<th>Delta (ms)</th>
			<th>Level</th>
			<th>Method</th>
			<th>Message</th>
		</tr>
		<xsl:apply-templates select="record"/>
	</table>
</xsl:template>

<xsl:template match="record">
	
	<xsl:variable name="myTime"><xsl:value-of select="millis"/></xsl:variable>
	<xsl:variable name="nIndex"><xsl:value-of select="position()"/></xsl:variable>
	<xsl:variable name="prevTime"><xsl:value-of select="/log/record[$nIndex - 1]/millis"/></xsl:variable>
	
	<tr>
		<td><xsl:value-of select="sequence"/></td>
		<td><xsl:value-of select="millis - $START_TIME_MS"/></td>
		<td>
			<xsl:if test="$nIndex > 1">
				<xsl:value-of select="$myTime - $prevTime"/>
			</xsl:if>
		</td>
		<td><xsl:value-of select="level"/></td>
		<td><xsl:value-of select="method"/></td>
		<td><xsl:value-of select="message"/></td>
	</tr>
</xsl:template>

</xsl:stylesheet>	