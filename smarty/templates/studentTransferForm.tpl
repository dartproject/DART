{*
 *  Copyright (C) 2011 author (email)
 *
 *  This program is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  as published by the Free Software Foundation; either version 2
 *  of the License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*}

{extends file="layout.tpl"}
{block name="title"}{/block}

{block name=css}
<link rel="stylesheet" type="text/css" href="js/extjs/resources/css/ext-all.css" />
{/block}

{block name="js"}
<script type="text/javascript" src="js/extjs/bootstrap.js"></script>
<script type="text/javascript" src="js/studentTransferForm.js"></script>

{/block}

{block name="body"}

<div id="transferForm" style="margin-bottom:20px"></div>


{/block}