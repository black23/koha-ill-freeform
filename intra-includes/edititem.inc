[% IF whole.error %]
[% IF whole.status == 'missing_type' %]
<p><em>Please Note:</em> Mandatory field Type is missing.</p>
[% ELSE %]
<p>Unhandled error</p>
[% END %]
[% END %]

<h2>Edit a manual ILL request</h2>
<form id="freeform_edit_form" method="POST" action=[% here %]>
  <fieldset class="rows">
    <legend>General details</legend>
    <ol id="general-freeform-fields">
      <li>
        <label class="required" for="type">Type:</label>
        <select name="type" id="type">
          <option value=""/>
          [% IF whole.value.other.type.lower == "book" %]
          <option value="book" selected="selected">Book</option>
          [% ELSE %]
          <option value="book">Book</option>
          [% END %]
          [% IF whole.value.other.type.lower == "chapter" %]
          <option value="chapter" selected="selected">Chapter</option>
          [% ELSE %]
          <option value="chapter">Chapter</option>
          [% END %]
          [% IF whole.value.other.type.lower == "journal" %]
          <option value="journal" selected="selected">Journal</option>
          [% ELSE %]
          <option value="journal">Journal</option>
          [% END %]
          [% IF whole.value.other.type.lower == "article" %]
          <option value="article" selected="selected">Journal article</option>
          [% ELSE %]
          <option value="article">Journal article</option>
          [% END %]
          [% IF whole.value.other.type.lower == "thesis" %]
          <option value="thesis" selected="selected">Thesis</option>
          [% ELSE %]
          <option value="thesis">Thesis</option>
          [% END %]
          [% IF whole.value.other.type.lower == "conference" %]
          <option value="conference" selected="selected">Conference</option>
          [% ELSE %]
          <option value="conference">Conference</option>
          [% END %]
          [% IF whole.value.other.type.lower == "other" %]
          <option value="other" selected="selected">Other</option>
          [% ELSE %]
          <option value="other">Other</option>
          [% END %]
        </select>
      </li>
    </ol>
  </fieldset>
  [% cwd = whole.cwd %]
  [% type = whole.value.other.type %]
  [% IF type %]
      [% INCLUDE "${cwd}/shared-includes/forms/${type}.inc" %]
  [% END %]
  <fieldset class="rows">
    <legend>Custom fields</legend>
    <ol id="freeform-fields">
      [% keys = whole.value.other.custom_key.split('\0') %]
      [% values = whole.value.other.custom_value.split('\0') %]
      [% i = 0 %]
      [% FOREACH key IN keys %]
      <li class="form-horizontal">
        <input type="text" class="custom-name" name="custom_key" value="[% key %]"><input type="text" name="custom_value" id="custom-value" value="[% values.$i %]">
        <button value="[% i %]" name="custom_delete" type="submit" class="btn btn-danger btn-sm delete-new-field">
            <span class="fa fa-delete"></span>Delete
        </button></li>
      </li>
      [% i = i + 1 %]
      [% END %]
    </ol>
    <button type="button" id="add-new-fields" class="btn btn-default">
      <span class="fa fa-plus"></span>
      Add new field
    </button> 
  </fieldset>
  <fieldset class="action">
    <input type="submit" value="Update"/>
    <a class="cancel" href="/cgi-bin/koha/ill/ill-requests.pl">Cancel</a>
  </fieldset>
  <input type="hidden" name="illrequest_id" value="[% whole.value.other.illrequest_id %]" />
  <input type="hidden" name="method" value="edititem" />
  <input type="hidden" name="stage" value="form" />
  <input type="hidden" name="backend" value="FreeForm" />
</form>
[% BLOCK backend_jsinclude %]
<script type="text/javascript">
    // <![CDATA[]
        document.addEventListener("DOMContentLoaded", function() {
            $('#add-new-fields').click(function(e) {
                e.preventDefault();
                var row = '<li class="form-horizontal">' +
                    '<input type="text" class="custom-name" name="custom_key">' +
                    '<input type="text" id="custom-value" name="custom_value"> '+
                    '<button type="button" class="btn btn-danger btn-sm ' +
                    'delete-new-field">' +
                    '<span class="fa fa-delete">' +
                    '</span>Delete</button></li>';
                $('#freeform-fields').append(row);
            });
            $('#freeform-fields').on('click', '.delete-new-field',
                function(event) {
                    event.preventDefault();
                    $(event.target).parent().remove();
                }
            );
            $('#type').change(function() {
                $('#freeform_edit_form').prepend(
                    '<input type="hidden" name="change_type" value="1" />'
                );
                $('#freeform_edit_form').submit();
            });
        });
    // ]]>
</script>
[% END %]
