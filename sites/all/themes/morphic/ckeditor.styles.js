if (typeof(CKEDITOR) !== 'undefined') {
  CKEDITOR.addStylesSet( 'drupal',
  [
    {
      name: 'Button',
      element: 'a',
      attributes: {
        class: 'usa-button'
      }
    },
    {
      name: 'Button - Gray',
      element: 'a',
      attributes: {
        class: 'usa-button usa-button-gray'
      }
    },
    {
      name: 'Button - Outline',
      element: 'a',
      attributes: {
        class: 'usa-button usa-button-outline'
      }
    },
    {
      name: 'Button - Outline Inverse',
      element: 'a',
      attributes: {
        class: 'usa-button usa-button-outline-inverse'
      }
    },
    {
      name: 'Button - Big',
      element: 'a',
      attributes: {
        class: 'usa-button usa-button-big'
      }
    },
    {
      name: 'Button - Secondary',
      element: 'a',
      attributes: {
        class: 'usa-button usa-button-secondary'
      }
    },
    {
      name: 'Borderless Table',
      element: 'table',
      attributes: {
        class: 'usa-table-borderless'
      }
    },
    {
      name: 'Lead Font',
      element: 'p',
      attributes: {
        class: 'usa-font-lead'
      }
    }
  ]);
}
